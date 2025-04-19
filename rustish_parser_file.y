%{
// Code for the bison file
// #include "lex.yy.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "ASTtree.h"

extern int yylineno;

void yyerror(const char *msg);
//void custom_error(SemanticError *error);
int yylex(void);
/* Our parser does not support:
a = [1, 2, 3, 4] // This array assignment syntax
*/

%}

%code requires {
   #include <iostream>
   #include <string>
   #include <vector>
   #include "ASTtree.h"
}

%union {
   ExpressionNode *expression_node;
   IdentifierNode *indentifier_node;
   NumberNode *number_node;
   VariableInfo *var_dec_node; // Changed
   StatementNode *statement_node;
   FuncDefNode *func_def_node;
   FuncBodyNode *func_body_node;
   MainDefNode *main_def_node;
   ProgramNode *program_node;

   FuncCallExpressionNode *func_call_exp_node;

   TypeNode *type_node;

   std::vector<FuncDefNode *> *func_def_list_node;

   std::vector<ExpressionNode *> *used_args_node;

   std::vector<StatementNode *> *statement_list_node;

   std::vector<VariableInfo *> *params_list_node;

   VarSymbolTable *decl_list_node;

   TokenData* token;
}

%type <program_node>        program
%type <func_def_list_node>  funcDefList
%type <main_def_node>       mainDef
%type <func_def_node>       funcDef
%type <params_list_node>    paramsList
%type <func_body_node>      funcBody
%type <statement_node>      statement
%type <statement_list_node> statementList
%type <indentifier_node>    identifier
%type <number_node>         number
%type <expression_node>     expression
%type <used_args_node>      usedArgs
%type <var_dec_node>        varDec
%type <type_node>           type
%type <decl_list_node>      localVarDecList
%type <func_call_exp_node>  funcCallExp

%define parse.error verbose

%token <token> MAIN LCURLY RCURLY IDENTIFIER SEMICOLON NUMBER ASSIGN PRINT READ COMMA
                    PRINTLN ARROW COLON FN I32 LET MUT BOOL FALSE TRUE INT_ARR BOOL_ARR
                    LPAREN RPAREN PLUS MINUS TIMES DIV MOD AND OR NOT IF ELSE WHILE RETURN 
                    LSQUARE RSQUARE NE EQ LT GT LE GE DOT LEN

%left EQ NE LT GT LE GE
%left PLUS MINUS OR
%left TIMES DIV MOD AND
%nonassoc NOT
%nonassoc ELSE

%start program

%%

program        : funcDefList mainDef {
                  $$ = new ProgramNode($2, $1); // Main first, then func_def_list
                  //abstract_syntax_tree = $$;
                  // No need to check functions, as all the code should be valid
                  // $$->check_funcs();
                  std::cout << "Done!\n";
               }

funcDefList    : funcDefList funcDef {
                     // Append the funcDef to funcDefList's list of function definitions
                     $1->push_back($2);
                     $$ = $1;
                     // Adds funcDef to funcDefList at the back
               }
               | /*epsilon*/ { // There are no functions (or no more functions?)
                  $$ = new std::vector<FuncDefNode *>;
               }

mainDef        : FN MAIN LPAREN RPAREN funcBody { // Just the funcBody this time, since name, return type, and param list are known
                  $$ = new MainDefNode($5);
               }

funcDef        : FN identifier LPAREN paramsList RPAREN ARROW type funcBody { // As with each of these funcDefs, create an instance of the function class with identifier, param list, type, and funcBody child
                  // Construct parameter table from parameter list
                  VarSymbolTable *var_table = new VarSymbolTable("var_table");
                  for (int i = 0; i < $4->size(); i++) {
                     var_table->insert($4->at(i)->name, $4->at(i));
                  }
                  $$ = new FuncDefNode($2, var_table, $4, $7, $8); // identifier, parameter table, parameter vector, return type, body
               }
               | FN identifier LPAREN paramsList RPAREN funcBody {
                  // Construct parameter table from parameter list
                  VarSymbolTable *var_table = new VarSymbolTable("var_table");
                  for (int i = 0; i < $4->size(); i++) {
                     var_table->insert($4->at(i)->name, $4->at(i));
                  }
                  $$ = new FuncDefNode($2, var_table, $4, NULL, $6); // Null for an empty return type i guess??
               }
               | FN identifier LPAREN RPAREN ARROW type funcBody {
                  $$ = new FuncDefNode($2, NULL, NULL, $6, $7); // Null for an empty param list
               }
               | FN identifier LPAREN RPAREN funcBody {
                  $$ = new FuncDefNode($2, NULL, NULL, NULL, $5);
               }

paramsList     : paramsList COMMA varDec {// Add varDec to the param list of the paramlist class
                  $3->initialized = true;
                  $1->push_back($3);
                  $$ = $1;
               }
               | varDec { // Create the ParamList out of the varDec
                  $$ = new std::vector<VariableInfo *>;
                  $1->initialized = true;
                  $$->push_back($1);
               }

varDec         : identifier COLON type { // Just a variable class with an identifier and type
                  VariableInfo *var_info = new VariableInfo;
                  var_info->name = *($1->identifier);
                  var_info->type = $3->type;
                  var_info->initialized = false;
                  var_info->line_num = yylineno;
                  $$ = var_info;
               }

type           : I32 {// For each of these, just make a type class with the type and maybe array size if we choose to modify this to include that in the grammar
                  $$ = new TypeNode(RustishType::i32_t); // Not entirely sure if this is the best convention??
               }
               | BOOL {
                  $$ = new TypeNode(RustishType::bool_t);
               }
               | LSQUARE I32 SEMICOLON number RSQUARE {
                  $$ = new TypeNode(RustishType::i32array_t); // TODO: Add the length into this, otherwise typechecking isn't possible with length
               }
               | LSQUARE BOOL SEMICOLON number RSQUARE {
                  $$ = new TypeNode(RustishType::boolarray_t);
               }
               | LSQUARE I32 RSQUARE {
                  $$ = new TypeNode(RustishType::i32array_t);
               }
               | LSQUARE BOOL RSQUARE {
                  $$ = new TypeNode(RustishType::boolarray_t);
               }

funcBody       : LCURLY localVarDecList statementList RCURLY { // Note that this doesn't leave room for variables mixed in with statements :/ Halterman's grammar verbatim
                  $$ = new FuncBodyNode($2, $3, yylineno); // Vector of varDec, statements
               }

localVarDecList: localVarDecList LET MUT varDec SEMICOLON {// Contains all local variable declarations in a function
                  $4->initialized = false;
                  $1->insert($4->name, $4); // Insert at beginning
                  $$ = $1;
               }
               |/* Epsilon */ {
                  $$ = new VarSymbolTable("localVarDecList");
               }

statementList  : statementList statement {// Contains all the statements in a function 
                  $1->push_back($2);
                  $$ = $1;
               }
               | /* Epsilon */ {// To start the statement list
                  $$ = new std::vector<StatementNode *>;
               }

statement      : SEMICOLON {
                  $$ = new StatementNode();
               }
               | identifier ASSIGN expression SEMICOLON {
                  $$ = new AssignmentStatementNode($1, $3);
               }
               | identifier PLUS ASSIGN expression SEMICOLON {
                  $$ = new OtherOpStatementNode($1, $4, OtherOperators::PLUS_OP);
               }
               | identifier MINUS ASSIGN expression SEMICOLON {
                  $$ = new OtherOpStatementNode($1, $4, OtherOperators::MINUS_OP);
               }
               | identifier TIMES ASSIGN expression SEMICOLON {
                  $$ = new OtherOpStatementNode($1, $4, OtherOperators::TIMES_OP);
               }
               | identifier DIV ASSIGN expression SEMICOLON {
                  $$ = new OtherOpStatementNode($1, $4, OtherOperators::DIV_OP);
               }
               | identifier MOD ASSIGN expression SEMICOLON {
                  $$ = new OtherOpStatementNode($1, $4, OtherOperators::MOD_OP);
               }
               | identifier LSQUARE expression RSQUARE ASSIGN expression SEMICOLON {// array[0] = 1
                  $$ = new ArrayAssignmentStatementNode($1, $3, $6);
               }
               | PRINT LPAREN usedArgs RPAREN SEMICOLON {
                  $$ = new PrintStatementNode($3);
               }
               | PRINTLN LPAREN usedArgs RPAREN SEMICOLON {
                  $$ = new PrintlnStatementNode($3);
               }
               | IF expression LCURLY statementList RCURLY {
                  $$ = new IfStatementNode($2, $4);
               }
               | IF expression LCURLY statementList RCURLY ELSE LCURLY statementList RCURLY {
                  $$ = new IfElseStatementNode($2, $4, $8);
               }
               | WHILE expression LCURLY statementList RCURLY {
                  $$ = new WhileStatementNode($2, $4);
               }
               | funcCallExp SEMICOLON {
                  $$ = new FuncCallStatementNode($1);
               }
               | RETURN expression SEMICOLON {
                  $$ = new ReturnStatementNode($2);
               }
               | RETURN SEMICOLON {
                  $$ = new ReturnStatementNode(new ExpressionNode());
               }

funcCallExp    : identifier LPAREN usedArgs RPAREN {
                  $$ = new FuncCallExpressionNode($1, $3, yylineno);
               }

usedArgs       : expression {
                  $$ = new std::vector<ExpressionNode *>;
                  $$->push_back($1);
               }
               | usedArgs COMMA expression {
                  $1->push_back($3);
                  $$ = $1;
               }
               | /* Epsilon */ {
                  $$ = nullptr;
               }

expression     : funcCallExp {
                  $$ = $1;
               }
               | LPAREN expression RPAREN {
                  $$ = $2;
               }
               | identifier DOT LEN {
                  $$ = new ArrayLengthExpressionNode($1, yylineno);
               }
               | identifier LSQUARE expression RSQUARE {
                  $$ = new ArrayAccessExpressionNode($1, $3, yylineno);
               }
               | number { 
                  $$ = new NumberExpressionNode($1, yylineno);
               }
               | identifier {
                  $$ = new IdentifierExpressionNode($1, yylineno);
               }
               | expression PLUS expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::PLUS_OP, yylineno);
               }
               | expression MINUS expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::MINUS_OP, yylineno);
               }
               | expression TIMES expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::TIMES_OP, yylineno);
               }
               | expression DIV expression {
                  if ($3 == 0) {
                     yyerror("Division by zero error!\n");
                  }
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::DIV_OP, yylineno);
               }
               | expression MOD expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::MOD_OP, yylineno);
               }
               | READ LPAREN RPAREN {
                  $$ = new ReadExpressionNode(yylineno);
               }
               | FALSE {
                  $$ = new FalseExpressionNode(yylineno);
               }
               | TRUE { 
                  $$ = new TrueExpressionNode(yylineno);
               }
               | expression AND expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::AND_OP, yylineno);
               }
               | expression OR expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::OR_OP, yylineno);
               }
               | expression EQ expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::EQ_OP, yylineno);
               }
               | expression NE expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::NE_OP, yylineno);
               }
               | expression LE expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::LE_OP, yylineno);
               }
               | expression GE expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::GE_OP, yylineno);
               }
               | expression GT expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::GT_OP, yylineno);
               }
               | expression LT expression {
                  $$ = new BinaryExpressionNode($1, $3, BinaryOperator::LT_OP, yylineno);
               }
               | NOT expression {
                  $$ = new NotExpressionNode($2, yylineno);
               }
               | MINUS expression {
                  $$ = new UnaryMinusExpressionNode($2, yylineno);
               }

identifier     : IDENTIFIER {
                  std::string *value = new std::string(yyval.token->value);
                  $$ = new IdentifierNode(value, yylineno);
               }

number         : NUMBER {
                  std::string *value = new std::string(yyval.token->value);
                  $$ = new NumberNode(value, yylineno);
               }

%%

extern FILE *yyin;

int yyparse();

int main(int argc, char **argv) {
   if (argc == 2) {
      yyin = fopen(argv[1], "r");
      if (yyin == NULL){
         printf("syntax: %s filename\n", argv[0]);
      }
   } else {
      printf("syntax: %s filename\n", argv[0]);
   }
   yyparse(); // Calls yylex() for tokens.

   return 0;
}

void yyerror(const char *msg) {
   printf("** Line %d: %s\n", yylineno, msg);
}