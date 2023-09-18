#include "driver.hh"
#include "utility.hh"
#include "parser.hh"

extern comparator resolveOption(string input);

Value *LogErrorV(const std::string Str) {
  std::cerr << Str << std::endl;
  return nullptr;
}

/*************************** Driver class *************************/
driver::driver(): trace_parsing (false), trace_scanning (false), ast_print (false) {
  context = new LLVMContext;
  module = new Module("Kaleidoscope", *context);
  builder = new IRBuilder(*context);
};

int driver::parse (const std::string &f) {
  file = f;
  location.initialize(&file);
  scan_begin();
  yy::parser parser(*this);
  parser.set_debug_level(trace_parsing);
  int res = parser.parse();
  scan_end();
  return res;
}

void driver::codegen() {
  if (ast_print) root->visit();
  std::cout << std::endl;
  root->codegen(*this);
};

// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of the function.  
// This is used for mutable variables etc.
AllocaInst *CreateEntryBlockAlloca(driver &drv, Function *TheFunction, Type* type, const std::string &VarName, int size = 0) {
  IRBuilder<> TmpB(&TheFunction->getEntryBlock(),TheFunction->getEntryBlock().begin());
  return TmpB.CreateAlloca(type, 0, VarName.c_str());
}

/********************** Handle Top Expressions ********************/
Value* TopExpression(ExprAST* E, driver& drv) {
  // Crea una funzione anonima anonima il cui body è un'espressione top-level
  // viene "racchiusa" un'espressione top-level
  E->toggle(); // Evita la doppia emissione del prototipo
  PrototypeAST *Proto = new PrototypeAST(
    "__espr_anonima"+std::to_string(++drv.Cnt),
		std::vector<std::pair<std::string, bool>>()
  );
  Proto->noemit();
  FunctionAST *F = new FunctionAST(std::move(Proto),E);
  auto *FnIR = F->codegen(drv);
  FnIR->eraseFromParent();
  return nullptr;
};

/************************ Expression tree *************************/
  // Inverte il flag che definisce le TopLevelExpression
  // ando viene chiamata
void ExprAST::toggle() {
  top = top ? false : true;
};

bool ExprAST::gettop() {
  return top;
};

/************************* Sequence tree **************************/
SeqAST::SeqAST(RootAST* first, RootAST* continuation):
  first(first), continuation(continuation) {};

void SeqAST:: visit() {
  if (first != nullptr) {
    first->visit();
  } else {
    if (continuation == nullptr) {
      return;
    };
  };
  std::cout << ";";
  continuation->visit();
};

Value *SeqAST::codegen(driver& drv) {
  if (first == nullptr) {
    return nullptr;
  } 
  first->codegen(drv);
  if (continuation != nullptr) {
    continuation->codegen(drv);
  } 
  return nullptr;
};


/******************** Unary Expression Tree **********************/
UnaryExprAST::UnaryExprAST(std::string Op, ExprAST* val):
  Op(Op), val(val) { top = false; };
 
void UnaryExprAST::visit() {
  std::cout << "(" << Op << " ";
  val->visit();
  std::cout << ")";
};

Value *UnaryExprAST::codegen(driver& drv) {
  if (gettop()) {
    return TopExpression(this, drv);
  } else {
    Value *value = val->codegen(drv);
    if (!val) return nullptr;
    switch (resolveOption(Op)) {
    case MIN:
      return drv.builder->CreateFMul(
        value,
        ConstantFP::get(*drv.context, APFloat(-1.0)),
        "mulregister"
      );
    default:  
      return LogErrorV("Operatore binario non supportato");
    }
  }
};

/******************** Binary Expression Tree **********************/
BinaryExprAST::BinaryExprAST(std::string Op, ExprAST* LHS, ExprAST* RHS):
  Op(Op), LHS(LHS), RHS(RHS) { top = false; };
 
void BinaryExprAST::visit() {
  std::cout << "(" << Op << " ";
  LHS->visit();
  if (RHS!=nullptr) RHS->visit();
  std::cout << ")";
};

Value *BinaryExprAST::codegen(driver& drv) {
  if (gettop()) {
    return TopExpression(this, drv);
  } else {
    // Special case '=' because we don't want to emit the LHS as an expression.
    if (Op == "=") {
      VariableExprAST *LHSE = dynamic_cast<VariableExprAST*>(LHS);
      if (!LHSE)
        return LogErrorV("destination of '=' must be a variable");

      Value *Variable = drv.NamedValues[LHSE->getName()];
      if (!Variable)
        return LogErrorV("Unknown variable name");
  
      Value* val = RHS->codegen(drv);
      if (!val)
        return nullptr;

      drv.builder->CreateStore(val, Variable);
      return val;
    }
    Value *L = LHS->codegen(drv);
    Value *R = RHS->codegen(drv);
    if (!L || !R) return nullptr;
    switch (resolveOption(Op)) {
    case SUM:
      return drv.builder->CreateFAdd(L,R,"addregister");
    case MIN:
      return drv.builder->CreateFSub(L,R,"subregister");
    case MUL:
      return drv.builder->CreateFMul(L,R,"mulregister");
    case DIV:
      return drv.builder->CreateFDiv(L,R,"divregister");
    case LT: {
        Value* cond_value = drv.builder->CreateFCmpULT(L,R,"ltregister");
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "ltregister");
        break;
      }
    case LE: {
        Value* cond_value = drv.builder->CreateFCmpULE(L,R,"lteregister");
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "lteregister");
        break;
      }
    case GT: {
        Value* cond_value = drv.builder->CreateFCmpUGT(L,R,"gtregister"); 
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "gtregister");
        break;
      }
    case GE: {
        Value* cond_value = drv.builder->CreateFCmpUGE(L,R,"gteregister");
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "gteregister");
        break;
      }
    case EQ: {
        Value* cond_value = drv.builder->CreateFCmpUEQ(L,R,"eqregister");
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "eqregister");
        break;
      }
    case NE: {
        Value* cond_value = drv.builder->CreateFCmpUNE(L,R,"neregister");
        return drv.builder->CreateUIToFP(cond_value, Type::getDoubleTy(*drv.context), "neregister");
        break;
      }
    case COLONS:
      return R;
    default:  
      return LogErrorV("Operatore binario non supportato");
    }
  }
};


/********************* Call Expression Tree ***********************/
CallExprAST::CallExprAST(std::string Callee, std::vector<ExprAST*> Args):
  Callee(Callee), Args(std::move(Args)) { 
    top = false; 
  };

void CallExprAST::visit() {
  std::cout << Callee << "( ";
  for (ExprAST* arg : Args) {
    arg->visit();
  };
  std::cout << ')';
};

Value *CallExprAST::codegen(driver& drv) {
  if (gettop()) {
    return TopExpression(this, drv);
  } else {
    // Cerchiamo la funzione nell'ambiente globale
    Function *CalleeF = drv.module->getFunction(Callee);
    if (!CalleeF)
      return LogErrorV("Funzione non definita");
    // Controlliamo che gli argomenti coincidano in numero coi parametri
    if (CalleeF->arg_size() != Args.size())
      return LogErrorV("Numero di argomenti non corretto");
    std::vector<Value *> ArgsV;
    for (int i = 0; i < Args.size(); i++) {
      Value * argVal = Args[i]->codegen(drv);

      if(CalleeF->getArg(i)->getType()->getTypeID() != argVal->getType()->getTypeID())
        return LogErrorV("Tipo del parametro non valido");

      ArgsV.push_back(argVal);
      if (!ArgsV.back())
	      return nullptr;
    }
    return drv.builder->CreateCall(CalleeF, ArgsV, "calltmp");
  }
}

/************************* Prototype Tree *************************/
PrototypeAST::PrototypeAST(std::string Name, std::vector<std::pair<std::string, bool>> Args): 
  Name(Name), Args(std::move(Args)) { 
    emit = true; 
  };

const std::string& PrototypeAST::getName() const { 
  return Name; 
};

const std::vector<std::pair<std::string, bool>>& PrototypeAST::getArgs() const { 
  return Args; 
};

void PrototypeAST::visit() {
  std::cout << "extern " << getName() << "( ";
  for (auto it=getArgs().begin(); it!= getArgs().end(); ++it) {
    std::cout << (*it).first << ' ';
  };
  std::cout << ')';
};

void PrototypeAST::noemit() { 
  emit = false; 
};

bool PrototypeAST::emitp() { 
  return emit; 
};

Function *PrototypeAST::codegen(driver& drv) {
  std::vector<Type*> Doubles;

  for(auto pair : Args) {
    if(pair.second)
      Doubles.push_back(Type::getDoublePtrTy(*drv.context));
    else
      Doubles.push_back(Type::getDoubleTy(*drv.context));
  }
  FunctionType *FT =
      FunctionType::get(Type::getDoubleTy(*drv.context), Doubles, false);
  Function *F =
      Function::Create(FT, Function::ExternalLinkage, Name, *drv.module);

  // Attribuiamo agli argomenti il nome dei parametri formali specificati dal programmatore
  unsigned Idx = 0;
  for (auto &Arg : F->args())
    Arg.setName(Args[Idx++].first);

  if (emitp()) {  // emitp() restituisce true se e solo se il prototipo è definito extern
    F->print(errs());
    fprintf(stderr, "\n");
  };
  
  return F;
}

/************************* Function Tree **************************/
FunctionAST::FunctionAST(PrototypeAST* Proto, ExprAST* Body):
  Proto(Proto), Body(Body) {};

void FunctionAST::visit() {
  std::cout << Proto->getName() << "( ";
  for (auto it=Proto->getArgs().begin(); it!= Proto->getArgs().end(); ++it) {
    std::cout << (*it).first << ' ';
  };
  std::cout << ") {"<<std::endl;
  Body->visit();
  std::cout <<std::endl<< '}';
};

Function *FunctionAST::codegen(driver& drv) {
  // Verifica che non esiste già, nel contesto, una funzione con lo stesso nome
  std::string name = Proto->getName();
  Function *TheFunction = drv.module->getFunction(name);
  // E se non esiste prova a definirla
  if (TheFunction) {
    LogErrorV("Funzione "+name+" già definita");
    return nullptr;
  }
  if (!TheFunction)
    TheFunction = Proto->codegen(drv);
  if (!TheFunction)
    return nullptr;  // Se la definizione "fallisce" restituisce nullptr

  // Crea un blocco di base in cui iniziare a inserire il codice
  BasicBlock *BB = BasicBlock::Create(*drv.context, "entry", TheFunction);
  drv.builder->SetInsertPoint(BB);

  // Registra gli argomenti nella symbol table
  drv.NamedValues.clear();
  for (auto &Arg : TheFunction->args()) {
    AllocaInst *Alloca = CreateEntryBlockAlloca(drv, TheFunction, Arg.getType(), Arg.getName().str(), 0);

    // Store the initial value into the alloca.
    drv.builder->CreateStore(&Arg, Alloca);
    
    // Add arguments to variable symbol table.
    drv.NamedValues[Arg.getName().str()] = Alloca;
  }

  if (Value *RetVal = Body->codegen(drv)) {
    // Termina la creazione del codice corrispondente alla funzione
    drv.builder->CreateRet(RetVal);

    // Effettua la validazione del codice e un controllo di consistenza
    verifyFunction(*TheFunction);

    TheFunction->print(errs());
    fprintf(stderr, "\n");
    return TheFunction;
  }

  // Errore nella definizione. La funzione viene rimossa
  TheFunction->eraseFromParent();
  return nullptr;
};


/************************* IfExpr Tree **************************/
IfExprAST::IfExprAST(ExprAST* Cond, ExprAST* Then, ExprAST* Else):
  Cond(Cond), Then(Then), Else(Else) { 
    top = false; 
  }

void IfExprAST::visit() {
  std::cout<<"se ";
  Cond->visit();
  std::cout<<std::endl<<"allora ";
  Then->visit();
  std::cout<<std::endl<<"altrimenti ";
  Else->visit();
};

Value *IfExprAST::codegen(driver& drv) {
  if (gettop()) 
    return TopExpression(this, drv);

  Value* condition = Cond->codegen(drv);

  condition = drv.builder->CreateFCmpONE(condition,ConstantFP::get(*drv.context,APFloat(0.0)),"iftest");

  Function* function = drv.builder->GetInsertBlock()->getParent();

  BasicBlock* ThenBB = BasicBlock::Create(*drv.context,"then", function);
  BasicBlock* ElseBB = BasicBlock::Create(*drv.context,"else");
  BasicBlock* MergeBB= BasicBlock::Create(*drv.context,"merge");

  AllocaInst *result = CreateEntryBlockAlloca(drv, function, Type::getDoubleTy(*drv.context), "ifresult", 0);

  drv.builder->CreateCondBr(condition,ThenBB,ElseBB);

  //Blocco Then
  drv.builder->SetInsertPoint(ThenBB);
  Value* ThenValue = Then->codegen(drv);
  drv.builder->CreateStore(ThenValue, result);
  drv.builder->CreateBr(MergeBB);
  
  function->getBasicBlockList().push_back(ElseBB);

  drv.builder->SetInsertPoint(ElseBB);
  Value* ElseValue = Else->codegen(drv);
  drv.builder->CreateStore(ElseValue, result);
  drv.builder->CreateBr(MergeBB);

  function->getBasicBlockList().push_back(MergeBB);

  drv.builder->SetInsertPoint(MergeBB);
  return drv.builder->CreateLoad(Type::getDoubleTy(*drv.context), result);
};

/************************* ForExpr Tree **************************/
ForExprAST::ForExprAST(ExprAST *Var, ExprAST* Start, ExprAST* End, ExprAST* Step, ExprAST* Body):
  Var(dynamic_cast<VariableExprAST*>(Var)), Start(Start), End(End), Step(Step), Body(Body) { 
    top = false; 
  }

void ForExprAST::visit() {
  std::cout<<"for "<<Var->getName()<<" = ";
  Start->visit();
  std::cout<<"to ";
  End->visit();
  std::cout<<" by ";
  if(Step != nullptr)
    Step->visit();
  else
    std::cout<<"1 ";
  std::cout<<"do "<<std::endl;
  Body->visit();
};

Value *ForExprAST::codegen(driver& drv) {
  if (gettop()) 
    return TopExpression(this, drv);

  Function *function = drv.builder->GetInsertBlock()->getParent();

  AllocaInst *startAlloca = CreateEntryBlockAlloca(drv, function, Type::getDoubleTy(*drv.context), Var->getName(), 0);

  // Emit the start code first, without 'variable' in scope.
  Value *StartVal = Start->codegen(drv);
  if (!StartVal)
    return nullptr;

  // Store the value into the alloca.
  drv.builder->CreateStore(StartVal, startAlloca);

  AllocaInst *OldVal = drv.NamedValues[Var->getName()];
  drv.NamedValues[Var->getName()] = startAlloca;

  Value *StepVal = nullptr;
  if (Step) {
    StepVal = Step->codegen(drv);
    if (!StepVal)
      return nullptr;
  } else {
    StepVal = ConstantFP::get(*drv.context, APFloat(1.0));
  }

  Value *EndCond = End->codegen(drv);
  if (!EndCond)
    return nullptr;
  EndCond = drv.builder->CreateFCmpONE(EndCond, ConstantFP::get(*drv.context, APFloat(0.0)), "loopcond");

  BasicBlock *LoopBB = BasicBlock::Create(*drv.context, "loop", function);
  BasicBlock *AfterBB = BasicBlock::Create(*drv.context, "afterloop");
  drv.builder->CreateCondBr(EndCond, LoopBB, AfterBB);

  // Start insertion in LoopBB.
  drv.builder->SetInsertPoint(LoopBB); 

  Value *BodyVal = Body->codegen(drv);
  if (!BodyVal)
    return nullptr;

  Value *CurVar = drv.builder->CreateLoad(Type::getDoubleTy(*drv.context), startAlloca, Var->getName());
  Value *NextVar = drv.builder->CreateFAdd(CurVar, StepVal, "nextvar");
  drv.builder->CreateStore(NextVar, startAlloca);

  EndCond = End->codegen(drv);
  if (!EndCond)
    return nullptr;
  EndCond = drv.builder->CreateFCmpONE(EndCond, ConstantFP::get(*drv.context, APFloat(0.0)), "loopcond");

  drv.builder->CreateCondBr(EndCond, LoopBB, AfterBB);
  
  function->getBasicBlockList().push_back(AfterBB);
  drv.builder->SetInsertPoint(AfterBB);

  if (OldVal)
    drv.NamedValues[Var->getName()] = OldVal;
  else
    drv.NamedValues.erase(Var->getName());

  return BodyVal;

};

/************************* VarExprAST Tree **************************/
VarExprAST::VarExprAST(std::vector<std::pair<std::string, ExprAST*>> VarNames, ExprAST* Body):
  VarNames(VarNames), Body(Body) { 
    top = false; 
  }

void VarExprAST::visit() {
  std::cout<<"define ";
  for(auto var : VarNames) {
    std::cout<<var.first<<" = ";
    var.second->visit();
  }
  std::cout<<"then do"<<std::endl;
  Body->visit();
  
};

Value *VarExprAST::codegen(driver& drv) {
  if (gettop()) 
    return TopExpression(this, drv);

  std::vector<AllocaInst *> OldBindings;

  Function *function = drv.builder->GetInsertBlock()->getParent();

  // Register all variables and emit their initializer.
  for (unsigned i = 0, e = VarNames.size(); i != e; ++i) {
    const std::string &VarName = VarNames[i].first;
    ExprAST *Init = VarNames[i].second;

    if(drv.NamedValues[VarName]) 
      return LogErrorV("Variabile già dichiarata");

    Value *InitVal;
    if (Init) {
      InitVal = Init->codegen(drv);
      if (!InitVal)
        return nullptr;
    } else { 
      InitVal = ConstantFP::get(*drv.context, APFloat(0.0));
    }
    AllocaInst *Alloca = CreateEntryBlockAlloca(drv, function, InitVal->getType(), VarName, 0);
    drv.builder->CreateStore(InitVal, Alloca);
    
    OldBindings.push_back(drv.NamedValues[VarName]);

    // Remember this binding.
    drv.NamedValues[VarName] = Alloca;
  }

  // Codegen the body, now that all vars are in scope.
  Value *BodyVal = Body->codegen(drv);
  if (!BodyVal)
    return nullptr;

  // Pop all our variables from scope.
  for (unsigned i = 0, e = VarNames.size(); i != e; ++i)
    drv.NamedValues[VarNames[i].first] = OldBindings[i];

  // Return the body computation.
  return BodyVal;
};


/************************* WhileExprAST Tree **************************/
WhileExprAST::WhileExprAST(ExprAST* Cond, ExprAST* Body):
  Cond(Cond), Body(Body){ 
    top = false; 
  }

void WhileExprAST::visit() {
    std::cout<<"while ";
    Cond->visit();
    std::cout<<" do "<<std::endl;
    Body->visit();
};

Value *WhileExprAST::codegen(driver& drv) {
  if (gettop()) 
    return TopExpression(this, drv);

  Function *function = drv.builder->GetInsertBlock()->getParent();

  BasicBlock *HeaderBB = BasicBlock::Create(*drv.context, "header", function);
  BasicBlock *LoopBB = BasicBlock::Create(*drv.context, "whilebody", function);
  BasicBlock *AfterBB = BasicBlock::Create(*drv.context, "afterwhile");

  drv.builder->CreateBr(HeaderBB);
  drv.builder->SetInsertPoint(HeaderBB); 

  Value *CondVal = Cond->codegen(drv);
  if (!CondVal)
    return nullptr;

  CondVal = drv.builder->CreateFCmpONE(CondVal, ConstantFP::get(*drv.context, APFloat(0.0)), "whilecond");

  // drv.builder->CreateBr(AfterBB);
  drv.builder->CreateCondBr(CondVal, LoopBB, AfterBB);
  drv.builder->SetInsertPoint(LoopBB); 

  Value *BodyVal = Body->codegen(drv);
  if (!BodyVal)
    return nullptr;

  drv.builder->CreateBr(HeaderBB);

  function->getBasicBlockList().push_back(AfterBB);
  drv.builder->SetInsertPoint(AfterBB);

  return BodyVal;
};

/********************* Number Expression Tree *********************/
NumberExprAST::NumberExprAST(double Val): Val(Val) { top = false; };
void NumberExprAST::visit() {
  std::cout << Val << " ";
};

Value *NumberExprAST::codegen(driver& drv) {  
  if (gettop()) return TopExpression(this, drv);
  else return ConstantFP::get(*drv.context, APFloat(Val));
};

/****************** Variable Expression TreeAST *******************/
VariableExprAST::VariableExprAST(std::string &Name):
  Name(Name) { top = false; };

const std::string& VariableExprAST::getName() const {
  return Name;
};

void VariableExprAST::visit() {
  std::cout << getName() << " ";
};

Value *VariableExprAST::codegen(driver& drv) {
  if (gettop()) {
    return TopExpression(this, drv);
  } else {
    AllocaInst* V = drv.NamedValues[Name];
    if (!V) LogErrorV("Variabile non definita");

    return drv.builder->CreateLoad(V->getAllocatedType(), V, Name);
  }
};

/****************** Array Expression TreeAST *******************/
ArrayExprAST::ArrayExprAST(std::string Varname, ExprAST* Size, std::vector<ExprAST*> Values, bool initialize):
  Varname(Varname), Size(Size), Values(Values), initialize(initialize) { 
    top = false; 
  }

void ArrayExprAST::visit() {
  if(initialize) {
    std::cout<<"{ ";
    for(auto val : Values) {
      val->visit();
    }
    std::cout<<"} ";
  } else {
    std::cout<<Varname + " at index ";
    Size->visit();
    if(Values.size()) {
      std::cout<<"= ";
      Values[0]->visit();
    }
  }
};

Value *ArrayExprAST::codegen(driver& drv) {
  if (gettop()) 
    return TopExpression(this, drv);

  Function *function = drv.builder->GetInsertBlock()->getParent();
  
  auto zero = ConstantInt::get(*drv.context, APInt(32, 0, true));

  if(initialize) {

    double dim = cast<ConstantFP>(Size->codegen(drv))->getValue().convertToFloat();
    if(dim < Values.size())
      return LogErrorV("Numero di elementi non corretto");
      
    ArrayType *doubleArrayType = ArrayType::get(Type::getDoubleTy(*drv.context), dim);
    AllocaInst *allocaArray = CreateEntryBlockAlloca(drv, function, doubleArrayType, Varname);

    for (int i = 0; i < Values.size(); i++) {
      Value* index = ConstantInt::get(*drv.context, APInt(32, i, true));
      Value* ptr = drv.builder->CreateInBoundsGEP(doubleArrayType, allocaArray, { zero, index });
      drv.builder->CreateStore(Values[i]->codegen(drv), ptr);
    }
    return allocaArray;
  }

  AllocaInst* arrayVar = drv.NamedValues[Varname];
  if (!arrayVar) 
    return LogErrorV(Varname + " non definito");  

  if (arrayVar->getAllocatedType()->getTypeID() != PointerType::PointerTyID)
    return LogErrorV(Varname + " non è un array");

  Value* indexVal = Size->codegen(drv);
  Value* arrayPtr =  drv.builder->CreateLoad(Type::getDoublePtrTy(*drv.context), arrayVar, "arrayptr");
  Value *arrayElement = nullptr;

  if(dyn_cast<ConstantFP>(indexVal)) {
    double dim = cast<ConstantFP>(indexVal)->getValue().convertToFloat();
    arrayElement = drv.builder->CreateInBoundsGEP(Type::getDoubleTy(*drv.context), arrayPtr, ConstantInt::get(*drv.context, APInt(32, dim, true)));
  } else {
    // è necessario prima castare da DOUBLE a FLOAT e poi da FLOAT a INT
    auto index = drv.builder->CreateFPToSI(drv.builder->CreateFPCast(indexVal, Type::getFloatTy(*drv.context)), Type::getInt32Ty(*drv.context));
    arrayElement = drv.builder->CreateInBoundsGEP(Type::getDoubleTy(*drv.context), arrayPtr, index);
  }
  
  if(Values.size()) {
    Value *val = Values[0]->codegen(drv);
    drv.builder->CreateStore(val, arrayElement);
    return val;
  } else {
    Value *loadedValue = drv.builder->CreateLoad(Type::getDoubleTy(*drv.context), arrayElement);
    return loadedValue;
  }
};
