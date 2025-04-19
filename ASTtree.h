#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "SymbolTable.h"

/*
Testing: ~ means error message may be not quite as helpful as it could be
[X] Assignment of wrong type to a declared variable
[X] Using an undeclared variable (rvalue)
[X] Assigning to an undeclared (lvalue)
[X] Use of an uninitialized variable
[X] Attempt to call an undefined function
[X] Passing wrong types of actual arguments to function call
[X] Passing wrong number of arguments to function call
[X~] Returning wrong type from function call (also returning something from a "void" function)
[X~] Missing return from function declared to return i32 or bool
[X] Mixed arithmetic (i32/bool)
[X] Arithmetic with bools
[X] Logical comparison with i32s
[X] Missing main function
[X] Missing let, mut, etc
[X] Non-i32 array indices
[X] Duplicate function names
[X] Duplicate local variables
[X] Non-Boolean expression in an if or while statement
[X] Variable declaration after executable code within a function definition
[X] Duplicate param names

Current known problems:
If/Else statement error line is garbage value
Array typechecking is iffy
Array literals don't work yet
*/

// (This comment was made from the start ~ around april 2nd or 3rd or so)
// My idea for this AST tree is this:  
/*  Expressions all have check_expression, and get fed multiple symbol tables
    Based on these symbol tables, they can check the types of their children
    Thus, typing must also trickle down, since the parser is bottom up - it will not wait for the VarDecNodes to be constructed before tackling the statements
    get_type is also a trickle-down thing, and stops whenever it hits something with a clear type
    Still waffling on having a void type, as functions must return something so it wouldn't be usefull in many scenarios
    Anyway though, get_type usually won't be called directly unless it is in the body of a check_expression function definition, since that is what will be doing the type checking
    Any variable declarations will disappear, as they will be added to the symbol tree and condensed into the declaration list

    For semantic naming errors, we check once we form the function list
    Program must thus have a check_funcs function, which checks whether functions have valid names AND then calls check_statements...
    functions (including main) should have a check_statements_list that then proceeds to call...
    statementList should have a function to check each statement, and each statement should have a function to check itself against a given variable symbol table
*/

// Type errors are dealt with in constructors of expression classes as necessary
// Semantic errors dealing with the symbol tree, however, are top down, as every symbol's validity may depend on things only contained in program
// Thus, we trickle down from checking functions to checking statement lists to statements to expressions

// The data structure that every token has
struct TokenData {
    const char *value;
    int line;
};

enum class BinaryOperator { PLUS_OP, MINUS_OP, TIMES_OP, DIV_OP, MOD_OP,
    AND_OP, OR_OP, LT_OP, GT_OP, LE_OP, GE_OP, EQ_OP, NE_OP
};

enum class OtherOperators { PLUS_OP, MINUS_OP, TIMES_OP, DIV_OP, MOD_OP };

class ASTNode {
public:
    virtual ~ASTNode() = 0;
};

class TypeNode: public ASTNode {
public:
    RustishType type;
    TypeNode(RustishType type);
    ~TypeNode() override;
};

class NumberNode: public ASTNode {
public:
    std::string *number;
    int line_num;

    NumberNode(std::string *number, int line_num);
    ~NumberNode() override;
};

class IdentifierNode: public ASTNode {
public:
    std::string *identifier;
    int line_num;

    IdentifierNode(std::string *identifier, int line_num);
    ~IdentifierNode() override;
};

class ExpressionNode: public ASTNode {
public:
    // Executive decision (impulsive for sure, but hopefully it works) - every expression has line number information (not sure how to do column)
    int line_num;
    ExpressionNode();
    virtual ~ExpressionNode();
    virtual void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars);
    virtual RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars);
};

class FuncCallExpressionNode: public ExpressionNode {
public:
    int line_num;
    IdentifierNode *identifier;
    std::vector<ExpressionNode *> *used_args;

    FuncCallExpressionNode(IdentifierNode *identifier, std::vector<ExpressionNode *> *used_args, int line_num);
    ~FuncCallExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Relies on the FuncDefNode symbol table
};

class NumberExpressionNode: public ExpressionNode {
public:
    int line_num;
    NumberNode *number;

    NumberExpressionNode(NumberNode *number, int line_num);
    ~NumberExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Probably empty, its literally just a number
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Just returns int, hopefully obvious
};

class IdentifierExpressionNode: public ExpressionNode {
public:
    int line_num;
    IdentifierNode *identifier;

    IdentifierExpressionNode(IdentifierNode *identifier, int line_num);
    ~IdentifierExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Likely will be empty, since this is also used for declaring variables
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Heavily relies on the symbol table
};

class BinaryExpressionNode: public ExpressionNode {
public:
    int line_num;
    ExpressionNode *left_operand;
    ExpressionNode *right_operand;
    BinaryOperator op;

    BinaryExpressionNode(ExpressionNode *left_operand, ExpressionNode *right_operand, BinaryOperator op, int line_num);
    ~BinaryExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Definitely depends on operands
};

class ReadExpressionNode: public ExpressionNode {
public:
    int line_num;
    ReadExpressionNode(int line_num);
    ~ReadExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Again, likely empty
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Int??? maybe
};

class TrueExpressionNode: public ExpressionNode {
public:
    int line_num;
    TrueExpressionNode(int line_num);
    ~TrueExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Also empty
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Just bool, hopefully obvious
};

class FalseExpressionNode: public ExpressionNode {
public:
    int line_num;
    FalseExpressionNode(int line_num);
    ~FalseExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Also empty
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Again, hopefully obvious
};

class NotExpressionNode: public ExpressionNode {
public:
    int line_num;
    ExpressionNode *operand;

    NotExpressionNode(ExpressionNode *operand, int line_num);
    ~NotExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Must make sure the operand is a bool!!!
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Again, bool
};

class UnaryMinusExpressionNode: public ExpressionNode {
public:
    int line_num;
    ExpressionNode *operand;

    UnaryMinusExpressionNode(ExpressionNode *operand, int line_num);
    ~UnaryMinusExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Operand should be an int
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Int
};

class ArrayAccessExpressionNode: public ExpressionNode {
public:
    int line_num;
    IdentifierNode *array;
    ExpressionNode *index;

    ArrayAccessExpressionNode(IdentifierNode *array, ExpressionNode *index, int line_num);
    ~ArrayAccessExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Should make sure the array exists, and the index is an int
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Depends on the symbol table, as it could be bool or int
};

class ArrayLengthExpressionNode: public ExpressionNode {
public:
    int line_num;
    IdentifierNode *array;

    ArrayLengthExpressionNode(IdentifierNode *array, int line_num);
    ~ArrayLengthExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Array should correspond to an array type
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class StatementNode: public ASTNode {
public:
    StatementNode();
    virtual ~StatementNode();
    virtual void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars);
};

class OtherOpStatementNode: public StatementNode {
public:
    IdentifierNode *identifier;
    ExpressionNode *operand;
    OtherOperators op;

    OtherOpStatementNode(IdentifierNode *identifier, ExpressionNode *operand, OtherOperators op);
    ~OtherOpStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class AssignmentStatementNode: public StatementNode {
public:
    IdentifierNode *identifier;
    ExpressionNode *expression;

    AssignmentStatementNode(IdentifierNode *identifier, ExpressionNode *expression);
    ~AssignmentStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class ArrayAssignmentStatementNode: public StatementNode {
public:
    IdentifierNode *identifier;
    ExpressionNode *index;
    ExpressionNode *expression;

    ArrayAssignmentStatementNode(IdentifierNode *identifier, ExpressionNode *index, ExpressionNode *expression);
    ~ArrayAssignmentStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class PrintStatementNode: public StatementNode {
public:
    std::vector<ExpressionNode *> *used_args;

    PrintStatementNode(std::vector<ExpressionNode *> *used_args);
    ~PrintStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class PrintlnStatementNode: public StatementNode {
public:
    std::vector<ExpressionNode *> *used_args;
    PrintlnStatementNode(std::vector<ExpressionNode *> *used_args);
    ~PrintlnStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class IfStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *statement_list;
    IfStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list);
    ~IfStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class IfElseStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *if_statement_list;
    std::vector<StatementNode *> *else_statement_list;
    IfElseStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *if_statement_list, std::vector<StatementNode *> *else_statement_list);
    ~IfElseStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class WhileStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *statement_list;
    WhileStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list);
    ~WhileStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class FuncCallStatementNode: public StatementNode {
public:
    FuncCallExpressionNode *func_call_exp;
    FuncCallStatementNode(FuncCallExpressionNode *);
    ~FuncCallStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
};

class ReturnStatementNode: public StatementNode {
public:
    ExpressionNode *expression;
    ReturnStatementNode(ExpressionNode *expression);
    ~ReturnStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    bool special_check(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars, std::string func);
};

class VarDecNode: public ASTNode {
public:
    IdentifierNode *identifier;
    TypeNode *type;
    VarDecNode(IdentifierNode *, TypeNode *);
    ~VarDecNode() override;
};

class FuncBodyNode: public ASTNode {
public:
    VarSymbolTable *local_var_decs;
    std::vector<StatementNode *> *statement_list;
    int line_num;
    FuncBodyNode(VarSymbolTable *local_var_decs, std::vector<StatementNode *> *statement_list, int line_num);
    ~FuncBodyNode() override;
    void check_statements(FuncSymbolTable *funcs, VarSymbolTable *params);
    void check_return_statement(FuncSymbolTable *funcs, VarSymbolTable *params, std::string func);
};

class FuncDefNode: public ASTNode {
public:
    IdentifierNode *name;
    VarSymbolTable *params_list;
    std::vector<VariableInfo *> *params_vector;
    TypeNode *return_type;
    FuncBodyNode *body;
    FuncDefNode(IdentifierNode *name, VarSymbolTable *params_list, std::vector<VariableInfo *> *params_vector, TypeNode *return_type, FuncBodyNode *body);
    ~FuncDefNode() override;
    void check_body(FuncSymbolTable *global_funcs);
};

class MainDefNode: public ASTNode {
public:
    FuncBodyNode *func_body;
    MainDefNode(FuncBodyNode *);
    ~MainDefNode() override;
    void check_body(FuncSymbolTable *table);
};

class ProgramNode: public ASTNode {
public:
    MainDefNode *main;
    std::vector<FuncDefNode *> *func_vector;
    FuncSymbolTable *func_table;

    ProgramNode(MainDefNode *main, std::vector<FuncDefNode *> *func_vector); // must be a vector so we can go through and check each, but we need to pass a symbol table for convinience of lookup
    ~ProgramNode() override;
    void check_funcs(); // Check each function's validity by calling it's individual check call
};

extern ProgramNode *abstract_syntax_tree;