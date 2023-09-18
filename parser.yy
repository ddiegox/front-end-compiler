%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.location.file none
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  #include <exception>
  class driver;
  class RootAST;
  class ExprAST;
  class FunctionAST;
  class SeqAST;
  class PrototypeAST;
  class IfExprAST;
  class ForExprAST;
  class BinaryExprAST;
  class VarExprAST;
  class WhileExprAST;
  class ArrayExprAST;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hh"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  ASSIGN      "="
  COLONS      ":"
  SEMICOLON  ";"
  COMMA      ","
  MINUS      "-"
  PLUS       "+"
  STAR       "*"
  SLASH      "/"
  LPAREN     "("
  RPAREN     ")"
  LBRACK    "["
  RBRACK     "]"
  LCURLY     "{"
  RCURLY     "}"
  MINOR      "<"
  MINOREQUAL "<="
  MAJOR      ">"
  MAJOREQUAL ">="
  EQUAL      "=="
  NOTEQUAL   "!="
  EXTERN     "extern"
  DEF        "def"
  IF         "if"
  THEN       "then"
  ELSE       "else"
  FLOWEND      "end"
  FOR         "for "
  IN          "in"
  VAR         "var"
  WHILE       "while"
;

%token <std::string> IDENTIFIER "identifier"
%token <double> NUMBER "number"
%type <ExprAST*> exp
%type <VarExprAST*> varexpr
%type <std::vector<std::pair<std::string, ExprAST*>>> varlist
%type <std::pair<std::string, ExprAST*>> coppia 
%type <ExprAST*> idexp
%type <std::vector<ExprAST*>> optexp
%type <std::vector<ExprAST*>> explist
%type <RootAST*> program
%type <RootAST*> top
%type <FunctionAST*> definition
%type <PrototypeAST*> external
%type <PrototypeAST*> proto
%type <IfExprAST*> ifexpr
%type <ForExprAST*> forexpr
%type <ExprAST*> step
%type <BinaryExprAST*> assignment
%type <std::vector<std::pair<std::string, bool>>> idseq
%type <WhileExprAST*> whileexpr
%type <ArrayExprAST*> arrayexpr

%left ":"
%left "="
%left "<" "<=" ">" ">=" "==" "!="
%left "+" "-"
%left "*" "/"

%%
%start startsymb;

startsymb:
program                                             { drv.root = $1; }

program:
  %empty                                            { $$ = new SeqAST(nullptr,nullptr); }
|  top ";" program                                  { $$ = new SeqAST($1,$3); };

top:
%empty                                              { $$ = nullptr; }
| definition                                        { $$ = $1; }
| external                                          { $$ = $1; }
| exp                                               { $$ = $1; $1->toggle(); };

definition:
  "def" proto exp                                   { $$ = new FunctionAST($2,$3); $2->noemit(); };

external:
  "extern" proto                                    { $$ = $2; };

proto:
  "identifier" "(" idseq ")"                        { $$ = new PrototypeAST($1,$3); };

idseq:
%empty                                              { std::vector<std::pair<std::string, bool>> args; $$ = args; }
| "identifier"  idseq                               { $2.insert($2.begin(), {$1, false}); $$ = $2; };
| "identifier" "[" "]"  idseq                       { $4.insert($4.begin(), {$1, true}); $$ = $4; };

exp:
  "number"                                          { $$ = new NumberExprAST($1); };       
|  "-" exp                                          { $$ = new UnaryExprAST("-", $2); }
| exp ":" exp                                       { $$ = new BinaryExprAST(":", $1, $3); }
| exp "+" exp                                       { $$ = new BinaryExprAST("+",$1,$3); }
| exp "-" exp                                       { $$ = new BinaryExprAST("-",$1,$3); }
| exp "*" exp                                       { $$ = new BinaryExprAST("*",$1,$3); }
| exp "/" exp                                       { $$ = new BinaryExprAST("/",$1,$3); }
| exp "<" exp                                       { $$ = new BinaryExprAST("<",$1,$3); }
| exp "<=" exp                                      { $$ = new BinaryExprAST("<=",$1,$3); }
| exp ">" exp                                       { $$ = new BinaryExprAST(">",$1,$3); }
| exp ">=" exp                                      { $$ = new BinaryExprAST(">=",$1,$3); }
| exp "==" exp                                      { $$ = new BinaryExprAST("==",$1,$3); }
| exp "!=" exp                                      { $$ = new BinaryExprAST("!=",$1,$3); }
| "(" exp ")"                                       { $$ = $2; }
| idexp                                             { $$ = $1; }
| ifexpr                                            { $$ = $1; }
| forexpr                                           { $$ = $1; }    
| varexpr                                           { $$ = $1; }
| assignment                                        { $$ = $1; }
| whileexpr                                         { $$ = $1; }
| arrayexpr                                         { $$ = $1; }

whileexpr:
  "while" exp "in" exp "end"                        {$$ = new WhileExprAST($2, $4); }

varexpr:
  "var" varlist "in" exp "end"                      { $$ = new VarExprAST($2, $4); }

varlist:
  coppia                                            { std::vector<std::pair<std::string, ExprAST*>> vars; vars.push_back($1); $$ = vars; }
| coppia "," varlist                                { $3.insert($3.begin(), $1); $$ = $3; };

coppia:
  "identifier"                                      {  $$ = make_pair($1, nullptr); }
| "identifier" "=" exp                              {  $$ = make_pair($1, $3); }
| "identifier" "[" "number" "]"                     {  $$ = make_pair($1, new ArrayExprAST($1, new NumberExprAST($3), {})); }
| "identifier" "[" "number" "]" "=" "{" explist "}" {  $$ = make_pair($1, new ArrayExprAST($1, new NumberExprAST($3), $7)); }

assignment:
 idexp "=" exp                                      { $$ = new BinaryExprAST("=", $1, $3); }

arrayexpr:
  "identifier" "[" exp "]"                          { $$ = new ArrayExprAST($1, $3, {}, false); }
| "identifier" "[" exp "]" "=" exp                  { std::vector<ExprAST*> args; args.push_back($6) ; $$ = new ArrayExprAST($1, $3, args, false); }

forexpr:
  "for " idexp "=" exp "," exp step "in" exp "end"  { $$ = new ForExprAST($2, $4, $6, $7, $9); }

step:
%empty                                              { $$ = nullptr; }
| "," exp                                           { $$ = $2; }

ifexpr:
  "if" exp "then" exp "else" exp "end"              { $$ = new IfExprAST($2, $4, $6);}

idexp:
  "identifier"                                      { $$ = new VariableExprAST($1); }
| "identifier" "(" optexp ")"                       { $$ = new CallExprAST($1,$3); };

optexp:
%empty                                              { std::vector<ExprAST*> args; $$ = args; }
| explist                                           { $$ = $1; };

explist:
  exp                                               { std::vector<ExprAST*> args; args.push_back($1); $$ = args; }
| exp "," explist                                   { $3.insert($3.begin(), $1); $$ = $3; };

%%

void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << "\n";
}
