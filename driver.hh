#ifndef DRIVER_HH
#define DRIVER_HH
/************ Header file per la generazione del codice oggetto *************/
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
/***************************************************************************/
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <variant>
#include "parser.hh"

using namespace llvm;

// Dichiarazione del prototipo yylex per Flex
// Flex va proprio a cercare YY_DECL perché
// deve espanderla (usando M4) nel punto appropriato
# define YY_DECL \
  yy::parser::symbol_type yylex (driver& drv)
// Per il parser è sufficiente una forward declaration
YY_DECL;

// Classe che organizza e gestisce il processo di compilazione
class driver
{
public:
  driver();
  LLVMContext *context;
  Module *module;
  IRBuilder<> *builder;
  std::map<std::string, AllocaInst*> NamedValues;
  std::unique_ptr<legacy::FunctionPassManager> TheFPM;
  static inline int Cnt=0; //Contatore incrementale, per identificare registri SSA
  RootAST* root;      // A fine parsing "punta" alla radice dell'AST
  int parse (const std::string& f);
  std::string file;
  bool trace_parsing; // Abilita le tracce di debug el parser
  void scan_begin (); // Implementata nello scanner
  void scan_end ();   // Implementata nello scanner
  bool trace_scanning;// Abilita le tracce di debug nello scanner
  yy::location location; // Utillizata dallo scanner per localizzare i token
  bool ast_print;
  void codegen();
};

// Classe base dell'intera gerarchia di classi che rappresentano
// gli elementi del programma
class RootAST {
public:
  virtual ~RootAST() {};
  virtual void visit() {};
  virtual Value *codegen(driver& drv) { return nullptr; };
};

// Classe che rappresenta la sequenza di statement
class SeqAST : public RootAST {
private:
  RootAST* first;
  RootAST* continuation;

public:
  SeqAST(RootAST* first, RootAST* continuation);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// ExprAST - Classe base per tutti i nodi espressione
class ExprAST : public RootAST {
protected:
  bool top;
public:
  virtual ~ExprAST() {};
  void toggle();
  bool gettop();
};

/// NumberExprAST - Classe per la rappresentazione di costanti numeriche
class NumberExprAST : public ExprAST {
private:
  double Val;

public:
  NumberExprAST(double Val);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// VariableExprAST - Classe per la rappresentazione di riferimenti a variabili
class VariableExprAST : public ExprAST {
private:
  std::string Name;
  
public:
  VariableExprAST(std::string &Name);
  const std::string &getName() const;
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// UnaryExprAST - Expression class for unary operators.
class UnaryExprAST : public ExprAST {
  std::string Op;
  ExprAST* val;

public:
  UnaryExprAST(std::string Op, ExprAST* val);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// BinaryExprAST - Classe per la rappresentazione di operatori binary
class BinaryExprAST : public ExprAST {
private:
  std::string Op;
  ExprAST* LHS;
  ExprAST* RHS;

public:
  BinaryExprAST(std::string Op, ExprAST* LHS, ExprAST* RHS);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// CallExprAST - Classe per la rappresentazione di chiamate di funzione
class CallExprAST : public ExprAST {
private:
  std::string Callee;
  std::vector<ExprAST*> Args;  // ASTs per la valutazione degli argomenti

public:
  CallExprAST(std::string Callee, std::vector<ExprAST*> Args);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// PrototypeAST - Classe per la rappresentazione dei prototipi di funzione
/// (nome, numero e nome dei parametri; in questo caso il tipo è implicito
/// perché unico)
class PrototypeAST : public RootAST {
private:
  std::string Name;
  std::vector<std::pair<std::string, bool>> Args;
  bool emit;

public:
  PrototypeAST(std::string Name, std::vector<std::pair<std::string, bool>> Args);
  const std::string &getName() const;
  const std::vector<std::pair<std::string, bool>> &getArgs() const; 
  void visit() override;
  Function *codegen(driver& drv) override;
  void noemit();
  bool emitp();
};

/// FunctionAST - Classe che rappresenta la definizione di una funzione
class FunctionAST : public RootAST {
private:
  PrototypeAST* Proto;
  ExprAST* Body;
  
public:
  FunctionAST(PrototypeAST* Proto, ExprAST* Body);
  void visit() override;
  Function *codegen(driver& drv) override;
};

/// IfExprAST - Expression class for if/then/else.
class IfExprAST : public ExprAST {
  ExprAST *Cond, *Then, *Else;
public:
  IfExprAST(ExprAST* Cond, ExprAST* Then, ExprAST* Else);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// ForExprAST - Expression class for for/in.
class ForExprAST : public ExprAST {
  VariableExprAST* Var;
  ExprAST *Start, *End, *Step, *Body;

public:
  ForExprAST(ExprAST* Var, ExprAST* Start, ExprAST* End, ExprAST* Step, ExprAST* Body);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// VarExprAST - Expression class for var/in
class VarExprAST : public ExprAST {
  std::vector<std::pair<std::string, ExprAST*>> VarNames;
  ExprAST* Body;

public:
  VarExprAST(std::vector<std::pair<std::string, ExprAST*>> VarNames, ExprAST* Body);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// WhileExprAST - Expression class for while/in
class WhileExprAST : public ExprAST {
  ExprAST *Cond, *Body;

public:
  WhileExprAST(ExprAST* Cond, ExprAST* Body);
  void visit() override;
  Value *codegen(driver& drv) override;
};

/// ArrayExprAST - Expression class double array
class ArrayExprAST : public ExprAST {
  std::string Varname;
  ExprAST* Size;
  std::vector<ExprAST*> Values;
  bool initialize;

public:
  ArrayExprAST(std::string Varname, ExprAST* Size, std::vector<ExprAST*> Values, bool initialize = true);
  void visit() override;
  Value *codegen(driver& drv) override;
};

#endif // ! DRIVER_HH
