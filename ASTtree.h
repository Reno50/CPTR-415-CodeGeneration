#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "SymbolTable.h"

/*
Current DOCUMENTED known problems:
If/Else statement error line is garbage value
Array typechecking is iffy
Array literals don't work yet
When checking for return statements, while statements will not have their statements checked - doing a comprehensive data flow analysis is the only way of truly implementing this feature
*/

/*
In this code generation assignment, all code given to our compiler is known to be correct
ASTNode has a virtual method called emit_code()
emit_code() writes all code to the file specified in write_code(std::string line), which is defined in ASTtree.cpp
*/

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
    virtual void emit_code(std::ofstream &context); // Emit MIPS assembly code
};

class TypeNode: public ASTNode {
public:
    RustishType type;
    int size;
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
    RustishType type; // Only filled in after checking expressions somtimes, for code gen purposes
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
    void emit_code(std::ofstream &context) override; // Emit the MIPS code, store this number on the stack
};

class IdentifierExpressionNode: public ExpressionNode {
public:
    int line_num;
    IdentifierNode *identifier;
    FuncSymbolTable *stored_func_defs;
    VarSymbolTable *stored_params;
    VarSymbolTable *stored_local_vars;

    IdentifierExpressionNode(IdentifierNode *identifier, int line_num);
    ~IdentifierExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Likely will be empty, since this is also used for declaring variables
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Heavily relies on the symbol table
    void emit_code(std::ofstream &context) override;
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
    void emit_code(std::ofstream &context);
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
    void emit_code(std::ofstream &context) override;
};

class FalseExpressionNode: public ExpressionNode {
public:
    int line_num;
    FalseExpressionNode(int line_num);
    ~FalseExpressionNode() override;
    void check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Also empty
    RustishType get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override; // Again, hopefully obvious
    void emit_code(std::ofstream &context) override;
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
    FuncSymbolTable *stored_func_defs;
    VarSymbolTable *stored_params;
    VarSymbolTable *stored_local_vars;

    AssignmentStatementNode(IdentifierNode *identifier, ExpressionNode *expression);
    ~AssignmentStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    void emit_code(std::ofstream &context) override;
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
    void emit_code(std::ofstream &context) override;
};

class PrintlnStatementNode: public StatementNode {
public:
    std::vector<ExpressionNode *> *used_args;
    PrintlnStatementNode(std::vector<ExpressionNode *> *used_args);
    ~PrintlnStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    void emit_code(std::ofstream &context) override;
};

class IfStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *statement_list;
    IfStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list);
    ~IfStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    void emit_code(std::ofstream &context);
};

class IfElseStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *if_statement_list;
    std::vector<StatementNode *> *else_statement_list;
    IfElseStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *if_statement_list, std::vector<StatementNode *> *else_statement_list);
    ~IfElseStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    void emit_code(std::ofstream &context);
};

class WhileStatementNode: public StatementNode {
public:
    ExpressionNode *condition;
    std::vector<StatementNode *> *statement_list;
    WhileStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list);
    ~WhileStatementNode() override;
    void check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) override;
    void emit_code(std::ofstream &context);
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
    void emit_code(std::ofstream &context) override; // Emit MIPS for the entire function
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
    void emit_code(std::ofstream &context) override; // Emit MIPS for the main function
};

class ProgramNode: public ASTNode {
public:
    MainDefNode *main;
    std::vector<FuncDefNode *> *func_vector;
    FuncSymbolTable *func_table;

    ProgramNode(MainDefNode *main, std::vector<FuncDefNode *> *func_vector); // must be a vector so we can go through and check each, but we need to pass a symbol table for convinience of lookup
    ~ProgramNode() override;
    void check_funcs(); // Check each function's validity by calling it's individual check call
    void emit_code(std::ofstream &context) override; // Emit MIPS code for the entire program
};

extern ProgramNode *abstract_syntax_tree;