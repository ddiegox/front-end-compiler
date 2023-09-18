// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "parser.hh"


// Unqualified %code blocks.
#line 35 "parser.yy"

# include "driver.hh"

#line 50 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

namespace yy {
#line 142 "parser.cc"

  /// Build a parser object.
  parser::parser (driver& drv_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      drv (drv_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_kind_type
  parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_arrayexpr: // arrayexpr
        value.YY_MOVE_OR_COPY< ArrayExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.YY_MOVE_OR_COPY< BinaryExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_step: // step
      case symbol_kind::S_idexp: // idexp
        value.YY_MOVE_OR_COPY< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forexpr: // forexpr
        value.YY_MOVE_OR_COPY< ForExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.YY_MOVE_OR_COPY< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifexpr: // ifexpr
        value.YY_MOVE_OR_COPY< IfExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.YY_MOVE_OR_COPY< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.YY_MOVE_OR_COPY< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varexpr: // varexpr
        value.YY_MOVE_OR_COPY< VarExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileexpr: // whileexpr
        value.YY_MOVE_OR_COPY< WhileExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_coppia: // coppia
        value.YY_MOVE_OR_COPY< std::pair<std::string, ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.YY_MOVE_OR_COPY< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varlist: // varlist
        value.YY_MOVE_OR_COPY< std::vector<std::pair<std::string, ExprAST*>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.YY_MOVE_OR_COPY< std::vector<std::pair<std::string, bool>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_arrayexpr: // arrayexpr
        value.move< ArrayExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< BinaryExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_step: // step
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_forexpr: // forexpr
        value.move< ForExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ifexpr: // ifexpr
        value.move< IfExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varexpr: // varexpr
        value.move< VarExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_whileexpr: // whileexpr
        value.move< WhileExprAST* > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_coppia: // coppia
        value.move< std::pair<std::string, ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varlist: // varlist
        value.move< std::vector<std::pair<std::string, ExprAST*>> > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::pair<std::string, bool>> > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_arrayexpr: // arrayexpr
        value.copy< ArrayExprAST* > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.copy< BinaryExprAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_step: // step
      case symbol_kind::S_idexp: // idexp
        value.copy< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forexpr: // forexpr
        value.copy< ForExprAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.copy< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_ifexpr: // ifexpr
        value.copy< IfExprAST* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.copy< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.copy< RootAST* > (that.value);
        break;

      case symbol_kind::S_varexpr: // varexpr
        value.copy< VarExprAST* > (that.value);
        break;

      case symbol_kind::S_whileexpr: // whileexpr
        value.copy< WhileExprAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_coppia: // coppia
        value.copy< std::pair<std::string, ExprAST*> > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.copy< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_varlist: // varlist
        value.copy< std::vector<std::pair<std::string, ExprAST*>> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.copy< std::vector<std::pair<std::string, bool>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_arrayexpr: // arrayexpr
        value.move< ArrayExprAST* > (that.value);
        break;

      case symbol_kind::S_assignment: // assignment
        value.move< BinaryExprAST* > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_step: // step
      case symbol_kind::S_idexp: // idexp
        value.move< ExprAST* > (that.value);
        break;

      case symbol_kind::S_forexpr: // forexpr
        value.move< ForExprAST* > (that.value);
        break;

      case symbol_kind::S_definition: // definition
        value.move< FunctionAST* > (that.value);
        break;

      case symbol_kind::S_ifexpr: // ifexpr
        value.move< IfExprAST* > (that.value);
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        value.move< PrototypeAST* > (that.value);
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        value.move< RootAST* > (that.value);
        break;

      case symbol_kind::S_varexpr: // varexpr
        value.move< VarExprAST* > (that.value);
        break;

      case symbol_kind::S_whileexpr: // whileexpr
        value.move< WhileExprAST* > (that.value);
        break;

      case symbol_kind::S_NUMBER: // "number"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_coppia: // coppia
        value.move< std::pair<std::string, ExprAST*> > (that.value);
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        value.move< std::vector<ExprAST*> > (that.value);
        break;

      case symbol_kind::S_varlist: // varlist
        value.move< std::vector<std::pair<std::string, ExprAST*>> > (that.value);
        break;

      case symbol_kind::S_idseq: // idseq
        value.move< std::vector<std::pair<std::string, bool>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (drv));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_arrayexpr: // arrayexpr
        yylhs.value.emplace< ArrayExprAST* > ();
        break;

      case symbol_kind::S_assignment: // assignment
        yylhs.value.emplace< BinaryExprAST* > ();
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_step: // step
      case symbol_kind::S_idexp: // idexp
        yylhs.value.emplace< ExprAST* > ();
        break;

      case symbol_kind::S_forexpr: // forexpr
        yylhs.value.emplace< ForExprAST* > ();
        break;

      case symbol_kind::S_definition: // definition
        yylhs.value.emplace< FunctionAST* > ();
        break;

      case symbol_kind::S_ifexpr: // ifexpr
        yylhs.value.emplace< IfExprAST* > ();
        break;

      case symbol_kind::S_external: // external
      case symbol_kind::S_proto: // proto
        yylhs.value.emplace< PrototypeAST* > ();
        break;

      case symbol_kind::S_program: // program
      case symbol_kind::S_top: // top
        yylhs.value.emplace< RootAST* > ();
        break;

      case symbol_kind::S_varexpr: // varexpr
        yylhs.value.emplace< VarExprAST* > ();
        break;

      case symbol_kind::S_whileexpr: // whileexpr
        yylhs.value.emplace< WhileExprAST* > ();
        break;

      case symbol_kind::S_NUMBER: // "number"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_coppia: // coppia
        yylhs.value.emplace< std::pair<std::string, ExprAST*> > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_optexp: // optexp
      case symbol_kind::S_explist: // explist
        yylhs.value.emplace< std::vector<ExprAST*> > ();
        break;

      case symbol_kind::S_varlist: // varlist
        yylhs.value.emplace< std::vector<std::pair<std::string, ExprAST*>> > ();
        break;

      case symbol_kind::S_idseq: // idseq
        yylhs.value.emplace< std::vector<std::pair<std::string, bool>> > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // startsymb: program
#line 106 "parser.yy"
                                                    { drv.root = yystack_[0].value.as < RootAST* > (); }
#line 881 "parser.cc"
    break;

  case 3: // program: %empty
#line 109 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = new SeqAST(nullptr,nullptr); }
#line 887 "parser.cc"
    break;

  case 4: // program: top ";" program
#line 110 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = new SeqAST(yystack_[2].value.as < RootAST* > (),yystack_[0].value.as < RootAST* > ()); }
#line 893 "parser.cc"
    break;

  case 5: // top: %empty
#line 113 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = nullptr; }
#line 899 "parser.cc"
    break;

  case 6: // top: definition
#line 114 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = yystack_[0].value.as < FunctionAST* > (); }
#line 905 "parser.cc"
    break;

  case 7: // top: external
#line 115 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 911 "parser.cc"
    break;

  case 8: // top: exp
#line 116 "parser.yy"
                                                    { yylhs.value.as < RootAST* > () = yystack_[0].value.as < ExprAST* > (); yystack_[0].value.as < ExprAST* > ()->toggle(); }
#line 917 "parser.cc"
    break;

  case 9: // definition: "def" proto exp
#line 119 "parser.yy"
                                                    { yylhs.value.as < FunctionAST* > () = new FunctionAST(yystack_[1].value.as < PrototypeAST* > (),yystack_[0].value.as < ExprAST* > ()); yystack_[1].value.as < PrototypeAST* > ()->noemit(); }
#line 923 "parser.cc"
    break;

  case 10: // external: "extern" proto
#line 122 "parser.yy"
                                                    { yylhs.value.as < PrototypeAST* > () = yystack_[0].value.as < PrototypeAST* > (); }
#line 929 "parser.cc"
    break;

  case 11: // proto: "identifier" "(" idseq ")"
#line 125 "parser.yy"
                                                    { yylhs.value.as < PrototypeAST* > () = new PrototypeAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<std::pair<std::string, bool>> > ()); }
#line 935 "parser.cc"
    break;

  case 12: // idseq: %empty
#line 128 "parser.yy"
                                                    { std::vector<std::pair<std::string, bool>> args; yylhs.value.as < std::vector<std::pair<std::string, bool>> > () = args; }
#line 941 "parser.cc"
    break;

  case 13: // idseq: "identifier" idseq
#line 129 "parser.yy"
                                                    { yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > ().insert(yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > ().begin(), {yystack_[1].value.as < std::string > (), false}); yylhs.value.as < std::vector<std::pair<std::string, bool>> > () = yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > (); }
#line 947 "parser.cc"
    break;

  case 14: // idseq: "identifier" "[" "]" idseq
#line 130 "parser.yy"
                                                    { yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > ().insert(yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > ().begin(), {yystack_[3].value.as < std::string > (), true}); yylhs.value.as < std::vector<std::pair<std::string, bool>> > () = yystack_[0].value.as < std::vector<std::pair<std::string, bool>> > (); }
#line 953 "parser.cc"
    break;

  case 15: // exp: "number"
#line 133 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new NumberExprAST(yystack_[0].value.as < double > ()); }
#line 959 "parser.cc"
    break;

  case 16: // exp: "-" exp
#line 134 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new UnaryExprAST("-", yystack_[0].value.as < ExprAST* > ()); }
#line 965 "parser.cc"
    break;

  case 17: // exp: exp ":" exp
#line 135 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST(":", yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ()); }
#line 971 "parser.cc"
    break;

  case 18: // exp: exp "+" exp
#line 136 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("+",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 977 "parser.cc"
    break;

  case 19: // exp: exp "-" exp
#line 137 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("-",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 983 "parser.cc"
    break;

  case 20: // exp: exp "*" exp
#line 138 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("*",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 989 "parser.cc"
    break;

  case 21: // exp: exp "/" exp
#line 139 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("/",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 995 "parser.cc"
    break;

  case 22: // exp: exp "<" exp
#line 140 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("<",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1001 "parser.cc"
    break;

  case 23: // exp: exp "<=" exp
#line 141 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("<=",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1007 "parser.cc"
    break;

  case 24: // exp: exp ">" exp
#line 142 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST(">",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1013 "parser.cc"
    break;

  case 25: // exp: exp ">=" exp
#line 143 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST(">=",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1019 "parser.cc"
    break;

  case 26: // exp: exp "==" exp
#line 144 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("==",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1025 "parser.cc"
    break;

  case 27: // exp: exp "!=" exp
#line 145 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new BinaryExprAST("!=",yystack_[2].value.as < ExprAST* > (),yystack_[0].value.as < ExprAST* > ()); }
#line 1031 "parser.cc"
    break;

  case 28: // exp: "(" exp ")"
#line 146 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[1].value.as < ExprAST* > (); }
#line 1037 "parser.cc"
    break;

  case 29: // exp: idexp
#line 147 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1043 "parser.cc"
    break;

  case 30: // exp: ifexpr
#line 148 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < IfExprAST* > (); }
#line 1049 "parser.cc"
    break;

  case 31: // exp: forexpr
#line 149 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ForExprAST* > (); }
#line 1055 "parser.cc"
    break;

  case 32: // exp: varexpr
#line 150 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < VarExprAST* > (); }
#line 1061 "parser.cc"
    break;

  case 33: // exp: assignment
#line 151 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < BinaryExprAST* > (); }
#line 1067 "parser.cc"
    break;

  case 34: // exp: whileexpr
#line 152 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < WhileExprAST* > (); }
#line 1073 "parser.cc"
    break;

  case 35: // exp: arrayexpr
#line 153 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ArrayExprAST* > (); }
#line 1079 "parser.cc"
    break;

  case 36: // whileexpr: "while" exp "in" exp "end"
#line 156 "parser.yy"
                                                    {yylhs.value.as < WhileExprAST* > () = new WhileExprAST(yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < ExprAST* > ()); }
#line 1085 "parser.cc"
    break;

  case 37: // varexpr: "var" varlist "in" exp "end"
#line 159 "parser.yy"
                                                    { yylhs.value.as < VarExprAST* > () = new VarExprAST(yystack_[3].value.as < std::vector<std::pair<std::string, ExprAST*>> > (), yystack_[1].value.as < ExprAST* > ()); }
#line 1091 "parser.cc"
    break;

  case 38: // varlist: coppia
#line 162 "parser.yy"
                                                    { std::vector<std::pair<std::string, ExprAST*>> vars; vars.push_back(yystack_[0].value.as < std::pair<std::string, ExprAST*> > ()); yylhs.value.as < std::vector<std::pair<std::string, ExprAST*>> > () = vars; }
#line 1097 "parser.cc"
    break;

  case 39: // varlist: coppia "," varlist
#line 163 "parser.yy"
                                                    { yystack_[0].value.as < std::vector<std::pair<std::string, ExprAST*>> > ().insert(yystack_[0].value.as < std::vector<std::pair<std::string, ExprAST*>> > ().begin(), yystack_[2].value.as < std::pair<std::string, ExprAST*> > ()); yylhs.value.as < std::vector<std::pair<std::string, ExprAST*>> > () = yystack_[0].value.as < std::vector<std::pair<std::string, ExprAST*>> > (); }
#line 1103 "parser.cc"
    break;

  case 40: // coppia: "identifier"
#line 166 "parser.yy"
                                                    {  yylhs.value.as < std::pair<std::string, ExprAST*> > () = make_pair(yystack_[0].value.as < std::string > (), nullptr); }
#line 1109 "parser.cc"
    break;

  case 41: // coppia: "identifier" "=" exp
#line 167 "parser.yy"
                                                    {  yylhs.value.as < std::pair<std::string, ExprAST*> > () = make_pair(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ExprAST* > ()); }
#line 1115 "parser.cc"
    break;

  case 42: // coppia: "identifier" "[" "number" "]"
#line 168 "parser.yy"
                                                    {  yylhs.value.as < std::pair<std::string, ExprAST*> > () = make_pair(yystack_[3].value.as < std::string > (), new ArrayExprAST(yystack_[3].value.as < std::string > (), new NumberExprAST(yystack_[1].value.as < double > ()), {})); }
#line 1121 "parser.cc"
    break;

  case 43: // coppia: "identifier" "[" "number" "]" "=" "{" explist "}"
#line 169 "parser.yy"
                                                    {  yylhs.value.as < std::pair<std::string, ExprAST*> > () = make_pair(yystack_[7].value.as < std::string > (), new ArrayExprAST(yystack_[7].value.as < std::string > (), new NumberExprAST(yystack_[5].value.as < double > ()), yystack_[1].value.as < std::vector<ExprAST*> > ())); }
#line 1127 "parser.cc"
    break;

  case 44: // assignment: idexp "=" exp
#line 172 "parser.yy"
                                                    { yylhs.value.as < BinaryExprAST* > () = new BinaryExprAST("=", yystack_[2].value.as < ExprAST* > (), yystack_[0].value.as < ExprAST* > ()); }
#line 1133 "parser.cc"
    break;

  case 45: // arrayexpr: "identifier" "[" exp "]"
#line 175 "parser.yy"
                                                    { yylhs.value.as < ArrayExprAST* > () = new ArrayExprAST(yystack_[3].value.as < std::string > (), yystack_[1].value.as < ExprAST* > (), {}, false); }
#line 1139 "parser.cc"
    break;

  case 46: // arrayexpr: "identifier" "[" exp "]" "=" exp
#line 176 "parser.yy"
                                                    { std::vector<ExprAST*> args; args.push_back(yystack_[0].value.as < ExprAST* > ()) ; yylhs.value.as < ArrayExprAST* > () = new ArrayExprAST(yystack_[5].value.as < std::string > (), yystack_[3].value.as < ExprAST* > (), args, false); }
#line 1145 "parser.cc"
    break;

  case 47: // forexpr: "for " idexp "=" exp "," exp step "in" exp "end"
#line 179 "parser.yy"
                                                    { yylhs.value.as < ForExprAST* > () = new ForExprAST(yystack_[8].value.as < ExprAST* > (), yystack_[6].value.as < ExprAST* > (), yystack_[4].value.as < ExprAST* > (), yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < ExprAST* > ()); }
#line 1151 "parser.cc"
    break;

  case 48: // step: %empty
#line 182 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = nullptr; }
#line 1157 "parser.cc"
    break;

  case 49: // step: "," exp
#line 183 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = yystack_[0].value.as < ExprAST* > (); }
#line 1163 "parser.cc"
    break;

  case 50: // ifexpr: "if" exp "then" exp "else" exp "end"
#line 186 "parser.yy"
                                                    { yylhs.value.as < IfExprAST* > () = new IfExprAST(yystack_[5].value.as < ExprAST* > (), yystack_[3].value.as < ExprAST* > (), yystack_[1].value.as < ExprAST* > ());}
#line 1169 "parser.cc"
    break;

  case 51: // idexp: "identifier"
#line 189 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new VariableExprAST(yystack_[0].value.as < std::string > ()); }
#line 1175 "parser.cc"
    break;

  case 52: // idexp: "identifier" "(" optexp ")"
#line 190 "parser.yy"
                                                    { yylhs.value.as < ExprAST* > () = new CallExprAST(yystack_[3].value.as < std::string > (),yystack_[1].value.as < std::vector<ExprAST*> > ()); }
#line 1181 "parser.cc"
    break;

  case 53: // optexp: %empty
#line 193 "parser.yy"
                                                    { std::vector<ExprAST*> args; yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1187 "parser.cc"
    break;

  case 54: // optexp: explist
#line 194 "parser.yy"
                                                    { yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1193 "parser.cc"
    break;

  case 55: // explist: exp
#line 197 "parser.yy"
                                                    { std::vector<ExprAST*> args; args.push_back(yystack_[0].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = args; }
#line 1199 "parser.cc"
    break;

  case 56: // explist: exp "," explist
#line 198 "parser.yy"
                                                    { yystack_[0].value.as < std::vector<ExprAST*> > ().insert(yystack_[0].value.as < std::vector<ExprAST*> > ().begin(), yystack_[2].value.as < ExprAST* > ()); yylhs.value.as < std::vector<ExprAST*> > () = yystack_[0].value.as < std::vector<ExprAST*> > (); }
#line 1205 "parser.cc"
    break;


#line 1209 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // parser::context.
  parser::context::context (const parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char parser::yypact_ninf_ = -73;

  const signed char parser::yytable_ninf_ = -6;

  const short
  parser::yypact_[] =
  {
       2,    47,    47,   -27,   -27,    47,   -22,   -21,    47,    11,
     -73,    15,   -73,    16,   -73,   -73,   340,   -73,   -73,   -73,
     -73,   -73,   -73,    49,    20,   245,    42,   -73,    47,   225,
      51,    57,     1,    33,    58,    97,    47,    47,   -73,     2,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      47,    47,   -73,    32,   340,    47,    47,    47,    34,    47,
     -21,    47,   264,    54,   -73,   283,   -73,   346,    20,    20,
     -73,   -73,    10,    10,    10,    10,    10,    10,   346,   -10,
      55,   204,   302,   340,    56,   116,   -73,   138,    47,   -73,
      66,    59,   -73,   -73,    47,    47,    68,   -73,   -73,   -73,
      47,    32,   160,   321,    60,   346,   -73,   -73,    47,    44,
      47,   340,    47,    61,   182,   -73,   -73
  };

  const signed char
  parser::yydefact_[] =
  {
       3,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      15,     0,     2,     0,     6,     7,     8,    34,    32,    33,
      35,    31,    30,    29,    16,     0,     0,    10,     0,     0,
      51,     0,    40,     0,    38,     0,    53,     0,     1,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    12,     9,     0,     0,     0,     0,     0,
       0,     0,    55,     0,    54,     0,     4,    17,    19,    18,
      20,    21,    22,    23,    24,    25,    26,    27,    44,    12,
       0,     0,     0,    41,     0,     0,    39,     0,     0,    52,
      45,     0,    13,    11,     0,     0,    42,    37,    36,    56,
       0,    12,     0,    48,     0,    46,    14,    50,     0,     0,
       0,    49,     0,     0,     0,    43,    47
  };

  const signed char
  parser::yypgoto_[] =
  {
     -73,   -73,    43,   -73,   -73,   -73,    79,   -69,     0,   -73,
     -73,    24,   -73,   -73,   -73,   -73,   -73,   -73,    80,   -73,
     -72
  };

  const signed char
  parser::yydefgoto_[] =
  {
       0,    11,    12,    13,    14,    15,    27,    80,    62,    17,
      18,    33,    34,    19,    20,    21,   109,    22,    23,    63,
      64
  };

  const signed char
  parser::yytable_[] =
  {
      16,    24,    25,    91,    57,    29,    26,    -5,    35,     1,
      92,    30,    32,     2,    58,    38,    99,    41,    42,    43,
      44,    39,    36,    79,    37,     3,     4,     5,    54,    43,
      44,     6,   106,     7,     8,     9,    10,    65,   113,    16,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    51,    53,     1,    81,    82,    83,     2,    85,
      56,    87,    36,    59,    60,    79,    89,    93,    84,   100,
      96,   104,     5,   101,   112,   110,     6,   115,     7,     8,
       9,    10,    66,    28,    86,     0,    31,     0,     0,     0,
       0,     0,     0,     0,   102,   103,     0,     0,     0,     0,
     105,    40,     0,     0,    41,    42,    43,    44,   111,     0,
       0,     0,   114,     0,    45,    46,    47,    48,    49,    50,
      40,     0,     0,    41,    42,    43,    44,    61,     0,     0,
       0,     0,     0,    45,    46,    47,    48,    49,    50,     0,
       0,     0,    40,     0,    97,    41,    42,    43,    44,     0,
       0,     0,     0,     0,     0,    45,    46,    47,    48,    49,
      50,     0,     0,     0,    40,     0,    98,    41,    42,    43,
      44,     0,     0,     0,     0,     0,     0,    45,    46,    47,
      48,    49,    50,     0,     0,     0,    40,     0,   107,    41,
      42,    43,    44,     0,     0,     0,     0,     0,     0,    45,
      46,    47,    48,    49,    50,     0,     0,     0,    40,     0,
     116,    41,    42,    43,    44,     0,     0,     0,     0,     0,
       0,    45,    46,    47,    48,    49,    50,     0,     0,    40,
       0,    94,    41,    42,    43,    44,     0,     0,     0,     0,
       0,     0,    45,    46,    47,    48,    49,    50,     0,    40,
       0,    55,    41,    42,    43,    44,     0,    52,     0,     0,
       0,     0,    45,    46,    47,    48,    49,    50,    40,     0,
      88,    41,    42,    43,    44,     0,     0,     0,     0,     0,
       0,    45,    46,    47,    48,    49,    50,    40,     0,     0,
      41,    42,    43,    44,     0,     0,     0,    90,     0,     0,
      45,    46,    47,    48,    49,    50,    40,     0,    95,    41,
      42,    43,    44,     0,     0,     0,     0,     0,     0,    45,
      46,    47,    48,    49,    50,    40,     0,   108,    41,    42,
      43,    44,     0,     0,     0,     0,     0,     0,    45,    46,
      47,    48,    49,    50,    40,     0,     0,    41,    42,    43,
      44,     0,     0,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    45,    46,    47,    48,    49,    50
  };

  const signed char
  parser::yycheck_[] =
  {
       0,     1,     2,    13,     3,     5,    33,     5,     8,     7,
      79,    33,    33,    11,    13,     0,    88,     7,     8,     9,
      10,     5,    11,    33,    13,    23,    24,    25,    28,     9,
      10,    29,   101,    31,    32,    33,    34,    37,   110,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,     3,    11,     7,    55,    56,    57,    11,    59,
       3,    61,    11,    30,     6,    33,    12,    12,    34,     3,
      14,     3,    25,    14,    30,    15,    29,    16,    31,    32,
      33,    34,    39,     4,    60,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    94,    95,    -1,    -1,    -1,    -1,
     100,     4,    -1,    -1,     7,     8,     9,    10,   108,    -1,
      -1,    -1,   112,    -1,    17,    18,    19,    20,    21,    22,
       4,    -1,    -1,     7,     8,     9,    10,    30,    -1,    -1,
      -1,    -1,    -1,    17,    18,    19,    20,    21,    22,    -1,
      -1,    -1,     4,    -1,    28,     7,     8,     9,    10,    -1,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    21,
      22,    -1,    -1,    -1,     4,    -1,    28,     7,     8,     9,
      10,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    -1,    -1,    -1,     4,    -1,    28,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,     4,    -1,
      28,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,    -1,    -1,     4,
      -1,    27,     7,     8,     9,    10,    -1,    -1,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,    -1,     4,
      -1,    26,     7,     8,     9,    10,    -1,    12,    -1,    -1,
      -1,    -1,    17,    18,    19,    20,    21,    22,     4,    -1,
       6,     7,     8,     9,    10,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    18,    19,    20,    21,    22,     4,    -1,    -1,
       7,     8,     9,    10,    -1,    -1,    -1,    14,    -1,    -1,
      17,    18,    19,    20,    21,    22,     4,    -1,     6,     7,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,
      18,    19,    20,    21,    22,     4,    -1,     6,     7,     8,
       9,    10,    -1,    -1,    -1,    -1,    -1,    -1,    17,    18,
      19,    20,    21,    22,     4,    -1,    -1,     7,     8,     9,
      10,    -1,    -1,     7,     8,     9,    10,    17,    18,    19,
      20,    21,    22,    17,    18,    19,    20,    21,    22
  };

  const signed char
  parser::yystos_[] =
  {
       0,     7,    11,    23,    24,    25,    29,    31,    32,    33,
      34,    36,    37,    38,    39,    40,    43,    44,    45,    48,
      49,    50,    52,    53,    43,    43,    33,    41,    41,    43,
      33,    53,    33,    46,    47,    43,    11,    13,     0,     5,
       4,     7,     8,     9,    10,    17,    18,    19,    20,    21,
      22,     3,    12,    11,    43,    26,     3,     3,    13,    30,
       6,    30,    43,    54,    55,    43,    37,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    33,
      42,    43,    43,    43,    34,    43,    46,    43,     6,    12,
      14,    13,    42,    12,    27,     6,    14,    28,    28,    55,
       3,    14,    43,    43,     3,    43,    42,    28,     6,    51,
      15,    43,    30,    55,    43,    16,    28
  };

  const signed char
  parser::yyr1_[] =
  {
       0,    35,    36,    37,    37,    38,    38,    38,    38,    39,
      40,    41,    42,    42,    42,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    43,    43,    43,    43,
      43,    43,    43,    43,    43,    43,    44,    45,    46,    46,
      47,    47,    47,    47,    48,    49,    49,    50,    51,    51,
      52,    53,    53,    54,    54,    55,    55
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     0,     3,     0,     1,     1,     1,     3,
       2,     4,     0,     2,     4,     1,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     5,     5,     1,     3,
       1,     3,     4,     8,     3,     4,     6,    10,     0,     2,
       7,     1,     4,     0,     1,     1,     3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\"=\"", "\":\"",
  "\";\"", "\",\"", "\"-\"", "\"+\"", "\"*\"", "\"/\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"<\"", "\"<=\"", "\">\"", "\">=\"",
  "\"==\"", "\"!=\"", "\"extern\"", "\"def\"", "\"if\"", "\"then\"",
  "\"else\"", "\"end\"", "\"for \"", "\"in\"", "\"var\"", "\"while\"",
  "\"identifier\"", "\"number\"", "$accept", "startsymb", "program", "top",
  "definition", "external", "proto", "idseq", "exp", "whileexpr",
  "varexpr", "varlist", "coppia", "assignment", "arrayexpr", "forexpr",
  "step", "ifexpr", "idexp", "optexp", "explist", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  parser::yyrline_[] =
  {
       0,   106,   106,   109,   110,   113,   114,   115,   116,   119,
     122,   125,   128,   129,   130,   133,   134,   135,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   156,   159,   162,   163,
     166,   167,   168,   169,   172,   175,   176,   179,   182,   183,
     186,   189,   190,   193,   194,   197,   198
  };

  void
  parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


} // yy
#line 1796 "parser.cc"

#line 200 "parser.yy"


void yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << "\n";
}
