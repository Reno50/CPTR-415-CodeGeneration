#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <typeinfo>
#include "ASTtree.h"

int if_counter = 0;
int loop_counter = 0;

std::string bin_op_to_string(BinaryOperator op) {
    switch (op) {
        case BinaryOperator::LT_OP:
            return "less than";
            break;
        case BinaryOperator::EQ_OP:
            return "equal to";
            break;
        case BinaryOperator::LE_OP:
            return "less than or equal to";
            break;
        case BinaryOperator::GE_OP:
            return "greater than or equal to";
            break;
        case BinaryOperator::GT_OP:
            return "greater than";
            break;
        case BinaryOperator::NE_OP:
            return "not equal";
            break;
    }
    return "";
}


void emit_var_lookup(std::ofstream &context, int stack_offset, std::string reg) {
    // Given the stack offset of a variable and the register to write to, emit code to put that variable in that register
    context << "# Load word at a frame pointer offset of " << stack_offset << " into register " << reg << "\n";
    context << "lw " << reg << ", " << stack_offset << "($fp)\n";
}

void pop_top_off_stack(std::ofstream &context, std::string reg) {
    context << "# Load top off stack into " << reg << " and decrement the stack\n";
    context << "lw " << reg << ", ($sp)\n";
    context << "addi $sp, $sp, 4\n";
}

void emit_var_store(std::ofstream &context, int stack_offset, std::string value_register) {
    context << "# Store word into variable with a frame pointer offset of " << stack_offset << "\n";
    context << "sw " << value_register << ", " << stack_offset << "($fp)\n";
}

void push_val_onto_stack(std::ofstream &context, std::string reg) {
    context << "# Store value in " << reg << " on top of the stack\n";
    context << "add $sp, $sp, -4\n";
    context << "sw " << reg << ", ($sp)\n";
}

void emit_comparison(std::ofstream &context, std::string result_reg, BinaryOperator op) {
    // Haven't tested this much yet
    context << "# Perform comparison: if ($t1 " << bin_op_to_string(op) << " $t0), set " << bin_op_to_string(op) << " = 1, else 0\n";

    // Use xor with 1 for not
    // Emit the appropriate branch instruction
    if (op == BinaryOperator::LT_OP)
        context << "slt $t2, $t1, $t0\n";
        // seq, neq, sne, slt, sgt, sle, sge
    else if (op == BinaryOperator::LE_OP)
        context << "sle $t2, $t1, $t0;\n";
    else if (op == BinaryOperator::GT_OP)
        context << "sgt $t2, $t1, $t0\n";
    else if (op == BinaryOperator::GE_OP)
        context << "sge $t2, $t1, $t0\n";
    else if (op == BinaryOperator::EQ_OP)
        context << "seq $t2, $t1, $t0\n";
    else if (op == BinaryOperator::NE_OP)
        context << "sne $t2, $t1, $t0\n";
    
    push_val_onto_stack(context, "$t2");
}

// In this file, I'll start from the top down, because I can and it makes it easier to have in my head
std::string type_to_string(RustishType r) {
    if (r == RustishType::bool_t) {
        return "bool_t";
    } else if (r == RustishType::i32_t) {
        return "i32_t";
    } else if (r == RustishType::boolarray_t) {
        return "boolarray_t";
    } else {
        return "i32array_t";
    }
}
void custom_error(SemanticError *error) {
    std::cout << error->msg << "\n";
}

ASTNode::~ASTNode() {};
void ASTNode::emit_code(std::ofstream &context) {};
ExpressionNode::ExpressionNode() {};
void ExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {};
RustishType ExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) { return RustishType::i32_t; std::cout << "Expression node get_type shouldn't have been called...\n"; };
StatementNode::StatementNode() {};
void StatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {};

ProgramNode::ProgramNode(MainDefNode *main, std::vector<FuncDefNode *> *func_vector):
    main(main), func_vector(func_vector) {
        // Construct func_table
        func_table = new FuncSymbolTable("func_table");
        for (int i = 0; i < func_vector->size(); i++) {
            FuncInfo *fun = new FuncInfo;
            fun->name = *(func_vector->at(i)->name->identifier);
            if (func_vector->at(i)->return_type != nullptr) {
                fun->return_type = (func_vector->at(i)->return_type->type);
                fun->void_func = false;
            } else {
                fun->return_type = RustishType::i32_t;
                fun->void_func = true;
            }
            fun->params = *(func_vector->at(i)->params_vector);
            func_table->insert(fun->name, fun);
        }
    };

ProgramNode::~ProgramNode() {
    delete main;
    delete func_vector;
    delete func_table;
}

void ProgramNode::check_funcs() {
    for (int i = 0; i < func_vector->size(); i++) {
        (func_vector)->at(i)->check_body(func_table); // Maybe doesn't work?
    }
    main->check_body(func_table);
}

void ProgramNode::emit_code(std::ofstream &context) {
    context << ".data\n";
    context << "_newline_char: .asciiz \"\\n\"\n";
    context << "_bool_true: .asciiz \"true\"\n";
    context << "_bool_false: .asciiz \"false\"\n";
    context << "# Will get filled in when we add variables\n";
    context << "\n";
    context << ".text\n";
    context << "# Emit the main function code from program\n";
    main->emit_code(context);
    context << "# Emit every other function code from program\n";
    for (int i = 0; i < func_vector->size(); i++) {
        func_vector->at(i)->emit_code(context);
    }
    context << "# All the labels for functions, including main: globl makes a label accessible across the entire program\n";
    context << "# Also, for simplicity's sake, I will put a _print_bool function here\n";
    context << "\n";
    context << "# Bool is passed in $a0\n";
    context << "_print_bool:\n";
    context << "    # Only using registers $a0 and $v0, so I don't think we need to save registers\n";
    context << "    beqz $a0, _print_false\n";
    context << "    # Else, print true\n";
    context << "    la $a0, _bool_true # Load string for false\n";
    context << "    li $v0, 4 # Syscall for string printing\n";
    context << "    syscall\n";
    context << "    jr $ra # Jump back\n";
    context << "\n";
    context << "_print_false:\n";
    context << "    la $a0, _bool_false # Load string for true\n";
    context << "    li $v0, 4 # Syscall for string printing\n";
    context << "    syscall\n";
    context << "    jr $ra # Jump back\n";
}

MainDefNode::MainDefNode(FuncBodyNode *func_body):
    func_body(func_body) {};

MainDefNode::~MainDefNode() {
    delete func_body;
}

void MainDefNode::emit_code(std::ofstream &context) {
    context << ".globl main\n";
    context << "main:\n";
    context << "# Now, all the statements that are part of main...\n";
    func_body->emit_code(context);
    context << "# Exit\n";
    context << "li $v0, 10\n";
    context << "syscall\n";
}

void MainDefNode::check_body(FuncSymbolTable *table) {
    func_body->check_statements(table, new VarSymbolTable("params")); // May cause a memory leak, as this isn't deleted since it was just declareds
    func_body->check_return_statement(table, new VarSymbolTable("params"), "main");
}

FuncDefNode::FuncDefNode(IdentifierNode *name, VarSymbolTable *params_list, std::vector<VariableInfo *> *params_vector, TypeNode *return_type, FuncBodyNode *body):
    name(name), params_list(params_list), params_vector(params_vector), return_type(return_type), body(body) {};

FuncDefNode::~FuncDefNode() {
    delete name;
    delete params_list;
    delete return_type;
    delete body;
}

void FuncDefNode::check_body(FuncSymbolTable *global_funcs) {
    body->check_statements(global_funcs, params_list);
    body->check_return_statement(global_funcs, params_list, (*name->identifier));
}

StatementNode::~StatementNode() = default;

ExpressionNode::~ExpressionNode() = default;

FuncBodyNode::FuncBodyNode(VarSymbolTable *local_var_decs, std::vector<StatementNode *> *statement_list, int line_num):
    local_var_decs(local_var_decs), statement_list(statement_list), line_num(line_num) {};

FuncBodyNode::~FuncBodyNode() {
    delete local_var_decs;
    delete statement_list;
}

void FuncBodyNode::check_statements(FuncSymbolTable *funcs, VarSymbolTable *params) {
    for (int i = 0; i < statement_list->size(); i++) {
        statement_list->at(i)->check_leaf_expressions(funcs, params, local_var_decs);
    }
}

void FuncBodyNode::check_return_statement(FuncSymbolTable *funcs, VarSymbolTable *params, std::string func) {
    int innaccurate_returns = 0;
    for (int i = 0; i < statement_list->size(); i++) {
        // According to stack overflow, a dynamic cast will return NULL if the class is not of that type
        if (auto ret_stmt = dynamic_cast<ReturnStatementNode *>(statement_list->at(i))) {
            if (ret_stmt->special_check(funcs, params, local_var_decs, func)) {
                innaccurate_returns++;
            }
        }
    }
    if (innaccurate_returns != 0) { // Only makes sure there is A correct return path - not that EVERY path returns correctly
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Function ";
        err->msg.append(func);
        err->msg.append(" had no return statement matching type ");
        if (func != "main") {
            if (!funcs->lookup(func)->void_func) {
                err->msg.append(type_to_string(funcs->lookup(func)->return_type));
            } else {
                err->msg.append("void -- thus, a return statement had a non-void return value");
            }
        } else {
            err->msg.append("void -- thus, a return statement had a non-void return value");
        }
        err->msg.append("!\n");
        custom_error(err);
        delete err;
    } else {
        if (funcs->lookup(func) && !funcs->lookup(func)->void_func) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = false;
            err->msg = "Function ";
            err->msg.append(func);
            err->msg.append(" had no return statement matching type ");
            if (funcs->lookup(func)->return_type == RustishType::i32_t) {
                err->msg.append("i32_t!");
            } else {
                err->msg.append("bool_t");
            }
            custom_error(err);
            delete err;
        }
    }
}

void FuncBodyNode::emit_code(std::ofstream &context) {
    /* First, store the frame pointer and return address onto the stack */
    context << "# Store the old frame pointer and the return address onto the stack - then, set the new frame pointer \n";
    context << "# To access these, do 4($fp) and 8($fp)\n";
    context << "sw $ra, -4($sp)\n";
    context << "sw $fp, -8($sp)\n";
    context << "addi $fp, $sp, -8\n";
    context << "addi $sp, $sp, -8\n";

    /* Next, emit code dealing with local variables -
        This will involve adding each to the stack, and setting each variable's stack offset
    */
    int current_offset = 0;
    for (auto j = local_var_decs->map.begin(); j != local_var_decs->map.end(); j++) {
        // Each variable has a size, and a stack offset
        if (j->second->size % 4 != 0) {
            std::cout << "Size of variable " << j->first << " didn't have size divisible by 4!\n";
        }
        context << "# Allocating space for " << j->first << ", which requires " << j->second->size << " bytes, and setting it to 0\n";
        for (int k = 0; k < j->second->size / 4; k++) { // First is name, second is VariableInfo
            // Frame pointer remains, stack pointer moves
            context << "add $sp, $sp, -4\n";
            context << "li $t0, 0\n";
            context << "sw $t0, ($sp)\n";
            current_offset -= 4;
        } // I'm sure this is a little unneccessary - but in the alarming case that something takes 5 bytes, it will technically be fine
        // This offset is from the 'top' of the stack, which is the highest address - stack grows from high to low numbers
        std::cout << "Setting variable " << j->second->name << "'s offset to " << current_offset << "\n";
        j->second->stack_offset = current_offset; // This will be 4 if it is the first variable - i.e., 4 minus what it was before
    }
    for (int i = 0; i < statement_list->size(); i++) {
        statement_list->at(i)->emit_code(context);
    }
}

VarDecNode::VarDecNode(IdentifierNode *identifier, TypeNode *type):
    identifier(identifier), type(type) {};

VarDecNode::~VarDecNode() {
    delete identifier;
    delete type;
}

ReturnStatementNode::ReturnStatementNode(ExpressionNode *expression):
    expression(expression) {};

ReturnStatementNode::~ReturnStatementNode() {
    delete expression;
}

void ReturnStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    expression->check_expression(func_defs, params, local_vars);
}

bool ReturnStatementNode::special_check(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars, std::string func) {
    // We also have to check the return type of this statement against the type returned by this function in the func_defs table, which is why this is a special check
    if (expression != nullptr && func_defs->lookup(func)->void_func) {
        SemanticError *err = new SemanticError;
        err->line_num = expression->line_num;
        err->type_error = true;
        err->msg = "Return type on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not null, but type was not specified in the function declaration!\n");
        custom_error(err);
        delete err;
        return false;
    }
    else if (expression == nullptr && !func_defs->lookup(func)->void_func) {
        SemanticError *err = new SemanticError;
        err->line_num = expression->line_num;
        err->type_error = true;
        err->msg = "Return type on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was null, but type was specified in the function declaration!\n");
        custom_error(err);
        delete err;
        return false;
    }
    else if (func_defs->lookup(func)->return_type != expression->get_type(func_defs, params, local_vars)) {
        SemanticError *err = new SemanticError;
        // Expression->line_num is a garbage value, so
        err->line_num = func_defs->lookup(func)->line_num;
        err->type_error = true;
        err->msg = "A return statement returned a type for function on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" that was not the return type stated in the function declaration!");
        custom_error(err);
        delete err;
        return false;
    }
    return true;
}

FuncCallStatementNode::FuncCallStatementNode(FuncCallExpressionNode *func_call_exp):
    func_call_exp(func_call_exp) {};

FuncCallStatementNode::~FuncCallStatementNode() {
    delete func_call_exp;
}

void FuncCallStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    func_call_exp->check_expression(func_defs, params, local_vars);
    // This check expression should check if the params match, as it has all of the information while the statement doesn't necessarily
}

WhileStatementNode::WhileStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list):
    condition(condition), statement_list(statement_list) {};

WhileStatementNode::~WhileStatementNode() {
    delete condition;
    delete statement_list;
}

void WhileStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    condition->check_expression(func_defs, params, local_vars);
    for (int i = 0; i < statement_list->size(); i++) {
        // Check every statement in the while statement
        statement_list->at(i)->check_leaf_expressions(func_defs, params, local_vars);
    }
    if (condition->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
        SemanticError *err = new SemanticError;
        err->line_num = condition->line_num;
        err->type_error = true;
        err->msg = "Condition in while statement on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type bool_t!");
        custom_error(err);
        delete err;
    }
}

void WhileStatementNode::emit_code(std::ofstream &context) {
    int label_id = loop_counter++; // global counter to make labels unique
    std::string loop_start = "_loop_start_" + std::to_string(label_id);
    std::string loop_end = "_loop_end_" + std::to_string(label_id);

    context << "# Begin while loop\n";
    context << loop_start << ":\n";

    condition->emit_code(context); // pushes result onto stack
    pop_top_off_stack(context, "$t0");
    context << "beq $t0, $zero, " << loop_end << "\n";

    // Emit body
    for (int i = 0; i < statement_list->size(); i++) {
        statement_list->at(i)->emit_code(context);
    }

    context << "j " << loop_start << "\n";
    context << loop_end << ":\n";
    context << "# End while loop\n";    
}

IfElseStatementNode::IfElseStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *if_statement_list, std::vector<StatementNode *> *else_statement_list):
    condition(condition), if_statement_list(if_statement_list), else_statement_list(else_statement_list) {};

IfElseStatementNode::~IfElseStatementNode() {
    delete condition;
    delete if_statement_list;
    delete else_statement_list;
}

void IfElseStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    condition->check_expression(func_defs, params, local_vars);
    // Check all the statements in each clause
    for (int i = 0; i < if_statement_list->size(); i++) {
        if_statement_list->at(i)->check_leaf_expressions(func_defs, params, local_vars);
    }
    for (int i = 0; i < else_statement_list->size(); i++) {
        else_statement_list->at(i)->check_leaf_expressions(func_defs, params, local_vars);
    }
    // If the If (condition <- ) isn't a boolean
    if (condition->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
        SemanticError *err = new SemanticError;
        err->line_num = condition->line_num;
        err->type_error = true;
        err->msg = "Condition in if-else statement on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type bool_t!");
        custom_error(err);
        delete err;
    }
}

void IfElseStatementNode::emit_code(std::ofstream &context) {
    int label_id = if_counter++;  // global counter for unique labels
    std::string else_label = "_else_branch_" + std::to_string(label_id);
    std::string end_label = "_end_if_else_" + std::to_string(label_id);

    context << "# Begin if-else statement\n";

    // Emit condition
    condition->emit_code(context);   // pushes condition result to stack
    pop_top_off_stack(context, "$t0");

    // Branch to else if condition is false (i.e., $t0 == 0)
    context << "beq $t0, $zero, " << else_label << "\n";

    // Emit then body
    context << "# Then branch\n";
    for (int i = 0; i < if_statement_list->size(); i++) {
        if_statement_list->at(i)->emit_code(context);
    }

    // Jump over else block
    context << "j " << end_label << "\n";

    // Else label
    context << else_label << ":\n";
    context << "# Else branch\n";
    for (int j = 0; j < else_statement_list->size(); j++) {
        else_statement_list->at(j)->emit_code(context);
    }

    // End label
    context << end_label << ":\n";
    context << "# End of if-else statement\n";
}


IfStatementNode::IfStatementNode(ExpressionNode *condition, std::vector<StatementNode *> *statement_list):
    condition(condition), statement_list(statement_list) {};

IfStatementNode::~IfStatementNode() {
    delete condition;
    delete statement_list;
}

void IfStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    // Again, check the condition and check each statement in the {} for validity
    condition->check_expression(func_defs, params, local_vars);
    for (int i = 0; i < statement_list->size(); i++) {
        statement_list->at(i)->check_leaf_expressions(func_defs, params, local_vars);
    }
    if (condition->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
        SemanticError *err = new SemanticError;
        err->line_num = condition->line_num;
        err->type_error = true;
        err->msg = "Condition in if-else statement on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type bool_t!");
        custom_error(err);
        delete err;
    }
}

void IfStatementNode::emit_code(std::ofstream &context) {
    int label_id = if_counter++;  // global counter for unique labels
    std::string end_label = "_end_if" + std::to_string(label_id);

    context << "# Begin if statement\n";

    // Emit condition
    condition->emit_code(context);   // pushes condition result to stack
    pop_top_off_stack(context, "$t0");

    // Branch to end if condition is false (i.e., $t0 == 0)
    context << "beq $t0, $zero, " << end_label << "\n";

    // Emit then body
    context << "# Then branch\n";
    for (int i = 0; i < statement_list->size(); i++) {
        statement_list->at(i)->emit_code(context);
    }

    // End label
    context << end_label << ":\n";
    context << "# End of if-else statement\n";
}

PrintlnStatementNode::PrintlnStatementNode(std::vector<ExpressionNode *> *used_args):
    used_args(used_args) {};

PrintlnStatementNode::~PrintlnStatementNode() {
    delete used_args;
}

void PrintlnStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    // Just check each used_args, they can be whatever type currently - arrays may result in some undefined behavior though
    for (int i = 0; i < used_args->size(); i++) {
        used_args->at(i)->check_expression(func_defs, params, local_vars);
    }
}

void PrintlnStatementNode::emit_code(std::ofstream &context) {
    // Emit MIPS assembly via write_code

    for (int i = 0; i < used_args->size(); i++) {
        used_args->at(i)->emit_code(context); // Pushes the expression's value onto the stack

        // Assume an integer - needs some work, as it assumes any variable is an int
        if (used_args->at(i)->type != RustishType::bool_t && used_args->at(i)->type != RustishType::boolarray_t && used_args->at(i)->type != RustishType::i32array_t) {
            // If it is an integer... or a type that isn't known
            // Now, the expression should have added one to the current stack - and $sp now points to the value
            context << "# Load value from the stack and print it, with a newline\n";
            context << "lw $a0, ($sp)\n";
            context << "addi $sp, $sp, 4\n";
            context << "li $v0, 1\n";
            context << "syscall\n";
        } else if (used_args->at(i)->type == RustishType::bool_t) {
            // If it is a bool...
            // Now, the expression should have added one to the current stack - and $sp now points to the value
            context << "# Load value from the stack and print it, with a newline\n";
            context << "lw $a0, ($sp)\n";
            context << "addi $sp, $sp, 4\n";
            context << "# Now, call the _print_bool function - printing the value that is currently in $a0\n";
            context << "# jal saves the return address automatically\n";
            context << "jal _print_bool\n";
            context << "\n";
        }
        // And the newline
        context << "la $a0, _newline_char\n";
        context << "li $v0, 4\n";
        context << "syscall\n";
    }
}

PrintStatementNode::PrintStatementNode(std::vector<ExpressionNode *> *used_args):
    used_args(used_args) {};

PrintStatementNode::~PrintStatementNode() {
    delete used_args;
}

void PrintStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    // Same as println
    for (int i = 0; i < used_args->size(); i++) {
        used_args->at(i)->check_expression(func_defs, params, local_vars);
    }
}

void PrintStatementNode::emit_code(std::ofstream &context) {
    // Same as println, arrays may result in no mips code emitted

    for (int i = 0; i < used_args->size(); i++) {
        used_args->at(i)->emit_code(context); // Pushes the expression's value onto the stack
        if (used_args->at(i)->type == RustishType::i32_t) {
            // If it is an integer...
            // Now, the expression should have added one to the current stack - and $sp now points to the value
            context << "# Load value from the stack and print it, with a newline\n";
            context << "lw $a0, ($sp)\n";
            context << "addi $sp, $sp, 4\n";
            context << "li $v0, 4\n";
            context << "syscall\n";
        } else if (used_args->at(i)->type == RustishType::bool_t) {
            // If it is a bool...
            // Now, the expression should have added one to the current stack - and $sp now points to the value
            context << "# Load value from the stack and print it, with a newline\n";
            context << "lw $a0, ($sp)\n";
            context << "addi $sp, $sp, 4\n";
            context << "# Now, is it a true or false? Value is currently in $a0\n";
            context << "beqz $a0, False\n";
            context << "# If it doesn't branch, it is a 1: thus, print true\n";
            context << "lw $a0, _bool_true\n";
            context << "False: \n";
            context << "    lw $a0, _bool_false\n";
            context << "li $v0, 4\n";
            context << "syscall\n";
        }
        context << "# Print space\n";
        context << "li $a0, 0x20\n";
        context << "li $v0, 11\n";
        context << "syscall\n";
    }
}

ArrayAssignmentStatementNode::ArrayAssignmentStatementNode(IdentifierNode *identifier, ExpressionNode *index, ExpressionNode *expression):
    identifier(identifier), index(index), expression(expression) {};

ArrayAssignmentStatementNode::~ArrayAssignmentStatementNode() {
    delete identifier;
    delete index;
    delete expression;
}

void ArrayAssignmentStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    // Throw an error if the identifier isn't of the type array, if index doesn't work out as an int, or if expression doesn't evaluate to the type of array
    VariableInfo *var = params->lookup(*(identifier->identifier)); // How does this even work? Idk
    if (var == nullptr) {
        var = local_vars->lookup(*(identifier->identifier));
    }
    // If it isn't found in either, throw an error
    if (var == nullptr) {
        SemanticError *err = new SemanticError;
        err->line_num = expression->line_num;
        err->type_error = false;
        err->msg = "Array identifier on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
    }
    // Check the expression next
    expression->check_expression(func_defs, params, local_vars);
    index->check_expression(func_defs, params, local_vars);

    // Now, if index isn't an int, throw an error
    if (index->get_type(func_defs, params, local_vars) != RustishType::i32_t) {
        SemanticError *err = new SemanticError;
        err->line_num = identifier->line_num;
        err->type_error = true;
        err->msg = "Array index on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type i32!");
        custom_error(err);
        delete err;
    }
}

AssignmentStatementNode::AssignmentStatementNode(IdentifierNode *identifier, ExpressionNode *expression):
    identifier(identifier), expression(expression) {};

AssignmentStatementNode::~AssignmentStatementNode() {
    delete identifier;
    delete expression;
}

void AssignmentStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    stored_func_defs = func_defs;
    stored_params = params;
    stored_local_vars = local_vars;
    // First, check identifier
    if (params->lookup(*(identifier->identifier)) == nullptr && local_vars->lookup(*(identifier->identifier)) == nullptr) {
        SemanticError *err = new SemanticError;
        err->line_num = identifier->line_num;
        err->type_error = false;
        err->msg = "lvalue identifier on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
        return;
    }
    // Next, check expression
    expression->check_expression(func_defs, params, local_vars);

    // Next, check if identifier and expression type are equal
    VariableInfo *var = params->lookup(*(identifier->identifier));
    if (var == nullptr) {
        var = local_vars->lookup(*(identifier->identifier));
    }
    var->initialized = true;
    if (var->type != expression->get_type(func_defs, params, local_vars)) {
        SemanticError *err = new SemanticError;
        err->line_num = identifier->line_num;
        err->type_error = true;
        err->msg = "rvalue expression on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" had a different type than the lvalue in the assignment!");
        custom_error(err);
        delete err;
    }
}

void AssignmentStatementNode::emit_code(std::ofstream &context) {
    // Lookup the variable's offset - find it in the tables
    VariableInfo *var = stored_local_vars->lookup(*(identifier->identifier));
    if (var == nullptr) {
        var = stored_params->lookup(*(identifier->identifier));
    }
    // That should work because we aren't passed incorrect code in this stage

    // First, emit code so the expression puts its value on the top of the stack...
    expression->emit_code(context);
    // Now that it is on the stack, store the value into var->stack_offset on the stack and decrement the stack (because we are done with the expression)
    pop_top_off_stack(context, "$t1"); // t1 arbitrary - used to be because $t0 is used
    emit_var_store(context, var->stack_offset, "$t1");
    // Done - we just stored the value in the variable
}

OtherOpStatementNode::OtherOpStatementNode(IdentifierNode *identifier, ExpressionNode *operand, OtherOperators op):
    identifier(identifier), operand(operand), op(op) {};

OtherOpStatementNode::~OtherOpStatementNode() {
    delete identifier;
    delete operand;
}

void OtherOpStatementNode::check_leaf_expressions(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    VariableInfo *var = params->lookup(*identifier->identifier);
    if (var == nullptr) {
        var = local_vars->lookup(*identifier->identifier);
    }
    if (var == nullptr) {
        // If variable isn't a known identifier, throw an error
        SemanticError *err = new SemanticError;
        err->line_num = operand->line_num;
        err->type_error = false;
        err->msg = "lvalue identifier on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
        return;
    }

    if (operand->get_type(func_defs, params, local_vars) == RustishType::i32_t) {
        SemanticError *err = new SemanticError;
        err->line_num = operand->line_num;
        err->type_error = true;
        err->msg = "Operand on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type i32!\n");
    }
    operand->check_expression(func_defs, params, local_vars);
}

ArrayLengthExpressionNode::ArrayLengthExpressionNode(IdentifierNode *array, int line_num):
    array(array), line_num(line_num) { type = RustishType::i32_t; };

ArrayLengthExpressionNode::~ArrayLengthExpressionNode() {
    delete array;
}

void ArrayLengthExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    // Check the symbol validity
    VariableInfo *var = params->lookup(*array->identifier);
    if (var == nullptr) {
        var = local_vars->lookup(*array->identifier);
    }

    if (var == nullptr) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Array lvalue of .len on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
        return;
    }
    // No other error types are possible, so
}

RustishType ArrayLengthExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    return RustishType::i32_t; // Don't throw an error here if it isn't found in the symbol table, as that already happened once
}

ArrayAccessExpressionNode::ArrayAccessExpressionNode(IdentifierNode *array, ExpressionNode *index, int line_num):
    array(array), index(index), line_num(line_num) { /* Type could be boolean OR int */ };

ArrayAccessExpressionNode::~ArrayAccessExpressionNode() {
    delete array;
    delete index;
}

void ArrayAccessExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    VariableInfo *var = params->lookup(*array->identifier);
    if (var == nullptr) {
        var = local_vars->lookup(*array->identifier);
    }
    if (var == nullptr) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Array accessed on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
        return;
    } else {
        if (var->type == RustishType::bool_t || var->type == RustishType::i32_t) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "Array accessed on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not an array!");
            custom_error(err);
            delete err;
            return;
        }
    }
    // Now check type of index
    if (index->get_type(func_defs, params, local_vars) != RustishType::i32_t) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = true;
        err->msg = "Index of array accessed on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type i32!");
        custom_error(err);
        delete err;
        return;
    }
    index->check_expression(func_defs, params, local_vars);
}

RustishType ArrayAccessExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    VariableInfo *var = local_vars->lookup(*array->identifier);
    if (var == nullptr) {
        var = params->lookup(*array->identifier);
    }
    if (var == nullptr) {
        type = RustishType::i32_t;
        return RustishType::i32_t; // Error! But we've likely already thrown the error, so
    } else {
        if (var->type == RustishType::boolarray_t) {
            type = RustishType::bool_t;
            return RustishType::bool_t;
        } else {
            type = RustishType::i32_t;
            return RustishType::i32_t; // Again, should throw error if it isn't a i32_array but it would've already done it
        }
    }
}

UnaryMinusExpressionNode::UnaryMinusExpressionNode(ExpressionNode *operand, int line_num):
    operand(operand), line_num(line_num) { type = RustishType::i32_t; };

UnaryMinusExpressionNode::~UnaryMinusExpressionNode() {
    delete operand;
}

void UnaryMinusExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    if (operand->get_type(func_defs, params, local_vars) != RustishType::i32_t) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = true;
        err->msg = "Operand in unary minus on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type i32!");
        custom_error(err);
        delete err;
        return;
    }
    operand->check_expression(func_defs, params, local_vars);
}

RustishType UnaryMinusExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    return RustishType::i32_t;
}

void UnaryMinusExpressionNode::emit_code(std::ofstream &context) {
    operand->emit_code(context);
    context << "# Unary minus - set number at top of stack to a negative number\n";
    context << "lw $t0, ($sp)\n";
    context << "neg $t0, $t0\n";
    context << "sw $t0, ($sp)\n";
}

NotExpressionNode::NotExpressionNode(ExpressionNode *operand, int line_num):
    operand(operand), line_num(line_num) { type = RustishType::bool_t; };

NotExpressionNode::~NotExpressionNode() {
    delete operand;
}

void NotExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    if (operand->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = true;
        err->msg = "Operand in not expression on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not of type bool!");
        custom_error(err);
        delete err;
        return;
    }
    operand->check_expression(func_defs, params, local_vars);
}

RustishType NotExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    return RustishType::bool_t;
}

FalseExpressionNode::FalseExpressionNode(int line_num):
    line_num(line_num) { type = RustishType::bool_t; };

FalseExpressionNode::~FalseExpressionNode() {};

void FalseExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {} // Nothing to do here

RustishType FalseExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {return RustishType::bool_t; };

void FalseExpressionNode::emit_code(std::ofstream &context) {
    context << "# Load false\n";
    context << "li $t0 0\n";
    context << "add $sp, $sp, -4\n";
    context << "sw $t0, ($sp)\n";
}

TrueExpressionNode::TrueExpressionNode(int line_num):
    line_num(line_num) { type = RustishType::bool_t; };

TrueExpressionNode::~TrueExpressionNode() {};

void TrueExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {} // Nothing to do here

RustishType TrueExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {return RustishType::bool_t; };

void TrueExpressionNode::emit_code(std::ofstream &context) {
    context << "# Load true\n";
    context << "li $t0 0\n";
    context << "add $sp, $sp, -4\n";
    context << "sw $t0, ($sp)\n";
}

ReadExpressionNode::ReadExpressionNode(int line_num):
    line_num(line_num) { type = RustishType::i32_t; };

ReadExpressionNode::~ReadExpressionNode() {};

void ReadExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {};

RustishType ReadExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {return RustishType::i32_t; };

BinaryExpressionNode::BinaryExpressionNode(ExpressionNode *left_operand, ExpressionNode *right_operand, BinaryOperator op, int line_num):
    left_operand(left_operand), right_operand(right_operand), op(op), line_num(line_num) {};

BinaryExpressionNode::~BinaryExpressionNode() {
    delete left_operand;
    delete right_operand;
}

void BinaryExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    left_operand->check_expression(func_defs, params, local_vars);
    right_operand->check_expression(func_defs, params, local_vars);
    // Check for type problems
    if (op == BinaryOperator::AND_OP || op == BinaryOperator::OR_OP) {
        // Check for bools
        if (left_operand->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "left operand in binary expression on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not of type bool, but operator was a bool operator!");
            custom_error(err);
            delete err;
        }
        if (right_operand->get_type(func_defs, params, local_vars) != RustishType::bool_t) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "right operand in binary expression on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not of type bool, but operator was a bool operator!");
            custom_error(err);
            delete err;
        }
        return;
    } else {
        // Check for ints
        if (left_operand->get_type(func_defs, params, local_vars) != RustishType::i32_t) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "left operand in binary expression on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not of type i32, but operator was an integer operator!");
            custom_error(err);
            delete err;
        }
        if (right_operand->get_type(func_defs, params, local_vars) != RustishType::i32_t) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "right operand in binary expression on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not of type i32, but operator was an integer operator!");
            custom_error(err);
            delete err;
        }
        return;
    }
}

RustishType BinaryExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    if (op == BinaryOperator::AND_OP || op == BinaryOperator::OR_OP || op == BinaryOperator::NE_OP || op == BinaryOperator::EQ_OP
    || op == BinaryOperator::LT_OP || op == BinaryOperator::LE_OP || op == BinaryOperator::GE_OP || op == BinaryOperator::GT_OP) {
        type = RustishType::bool_t;
        return RustishType::bool_t;
    } else {
        type = RustishType::i32_t;
        return RustishType::i32_t;
    }
}

void BinaryExpressionNode::emit_code(std::ofstream &context) {
    context << "# Beginning binary operator code\n";
    left_operand->emit_code(context);
    right_operand->emit_code(context);
    context << "# Now perform the operation and store the result in the stack\n";
    context << "# Pop right operand off\n";
    pop_top_off_stack(context, "$t0");
    context << "# Pop left operand off\n";
    pop_top_off_stack(context, "$t1");
    switch (op) {
        case BinaryOperator::PLUS_OP:
            context << "# Perform addition into t2\n";
            context << "add $t2, $t0, $t1\n";
            break;
        case BinaryOperator::MINUS_OP:
            context << "# Perform subtraction into t2\n";
            context << "sub $t2, $t1, $t0\n";
            break;
        case BinaryOperator::TIMES_OP:
            context << "# Perform multiplication into t2\n";
            context << "mult $t0, $t1\n";
            context << "mflo $t2\n";
            break;
        case BinaryOperator::DIV_OP:
            context << "# Perform division into t2\n";
            context << "div $t1, $t0\n";
            context << "mflo $t2\n";
            break;
        case BinaryOperator::MOD_OP:
            context << "# Perform modulo into t2\n";
            context << "div $t1, $t0\n";
            context << "mfhi $t2\n";
            break;
        case BinaryOperator::AND_OP:
            context << "# Perform and into t2\n";
            context << "and $t2, $t0, $t1\n";
            break;
        case BinaryOperator::OR_OP:
            context << "# Perform or into t2\n";
            context << "or $t2, $t0, $t1\n";
            break;
        case BinaryOperator::LT_OP:
            emit_comparison(context, "$t2", BinaryOperator::LT_OP);
            break;
        case BinaryOperator::EQ_OP:
            emit_comparison(context, "$t2", BinaryOperator::EQ_OP);
            break;
        case BinaryOperator::LE_OP:
            emit_comparison(context, "$t2", BinaryOperator::LE_OP);
            break;
        case BinaryOperator::GE_OP:
            emit_comparison(context, "$t2", BinaryOperator::GE_OP);
            break;
        case BinaryOperator::GT_OP:
            emit_comparison(context, "$t2", BinaryOperator::GT_OP);
            break;
        case BinaryOperator::NE_OP:
            emit_comparison(context, "$t2", BinaryOperator::NE_OP);
            break;
    }
    context << "# Put result on the stack\n";
    push_val_onto_stack(context, "$t2");
}

IdentifierExpressionNode::IdentifierExpressionNode(IdentifierNode *identifier, int line_num):
    identifier(identifier), line_num(line_num) {};

IdentifierExpressionNode::~IdentifierExpressionNode() {
    delete identifier;
}

void IdentifierExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    stored_func_defs = func_defs;
    stored_params = params;
    stored_local_vars = local_vars; // Crappy workaround because I didn't store these initially - sorry
    VariableInfo *var = params->lookup(*identifier->identifier);
    if (var == nullptr) {
        var = local_vars->lookup(*identifier->identifier);
    }

    if (var != nullptr && !var->initialized && (var->type == RustishType::i32_t || var->type == RustishType::bool_t)) { // Arrays don't need to be initialized --- TODO
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Identifier ";
        err->msg.append(*identifier->identifier);
        err->msg.append(" on line ");
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not assigned yet!");
        custom_error(err);
        delete err;
    }

    FuncInfo *func = func_defs->lookup(*identifier->identifier);

    if (var == nullptr && func == nullptr) {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Identifier ";
        err->msg.append(*identifier->identifier);
        err->msg.append(" on line ");
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" was not declared!");
        custom_error(err);
        delete err;
    }
}

RustishType IdentifierExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    VariableInfo *var = params->lookup(*identifier->identifier);
    if (var == nullptr) {
        var = local_vars->lookup(*identifier->identifier);
    }
    if (var != nullptr) {
        type = var->type;
        return var->type;
    } else {
        FuncInfo *func = func_defs->lookup(*identifier->identifier);
        if (func != nullptr && !func->void_func) {
            type = func->return_type;
            return func->return_type;
        } else if (func != nullptr) {
            // Error, since we shouldn't be getting the type of this expression since it evaluates to nothing
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = true;
            err->msg = "Function identifier on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was void, but seems to be used as a valid value!");
            custom_error(err);
            delete err;
            type = RustishType::i32_t; // Defaults to i32
        } else {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = false;
            err->msg = "Identifier ";
            err->msg.append(*identifier->identifier);
            err->msg.append(" on line ");
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" was not declared!");
            custom_error(err);
            delete err;
            type = RustishType::i32_t;
        }
    }
    type = RustishType::i32_t;
    return RustishType::i32_t;
}

void IdentifierExpressionNode::emit_code(std::ofstream &context) {
    // Using the stored tables, find the stack offset
    // Then, load it into $t0 - although I'm not too sure about this one -
    // What if you have x = a + b? If a and b are BOTH stored in $t0, -- oh wait - it can emit the code for one, then move it to $t1, and all is well - nevermind then
    VariableInfo *var = stored_local_vars->lookup(*(identifier->identifier));
    if (var == nullptr) {
        var = stored_params->lookup(*(identifier->identifier));
    }
    if (var == nullptr) {
        std::cout << "Compilation problem! Couldn't find the identifier " << *(identifier->identifier) << "!\n";
        return;
    }
    context << "# Load variable " << *(identifier->identifier) << " into $t0, and put it on the stack at the end\n";
    context << "lw $t0, " << var->stack_offset << "($fp)\n";
    context << "add $sp, $sp, -4\n";
    context << "sw $t0, ($sp)\n";
    context << "\n";
}

NumberExpressionNode::NumberExpressionNode(NumberNode *number, int line_num):
    number(number), line_num(line_num) { type = RustishType::i32_t; };

NumberExpressionNode::~NumberExpressionNode() {
    delete number;
}

void NumberExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    return; // A number literal need not stoop so low as to check this
}

RustishType NumberExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    return RustishType::i32_t;
}

void NumberExpressionNode::emit_code(std::ofstream &context) {
    context << "# Load number\n";
    context << "li $t0, " << *(number->number) << "\n";
    context << "add $sp, $sp, -4\n";
    context << "sw $t0, ($sp)\n";
}

FuncCallExpressionNode::FuncCallExpressionNode(IdentifierNode *identifier, std::vector<ExpressionNode *> *used_args, int line_num):
    identifier(identifier), used_args(used_args), line_num(line_num) {};

FuncCallExpressionNode::~FuncCallExpressionNode() {
    delete identifier;
    delete used_args;
}

void FuncCallExpressionNode::check_expression(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    FuncInfo *func = func_defs->lookup(*identifier->identifier);
    if (func != nullptr) {
        // Check each parameter to make sure they are in the symbol table AND are typed correctly
        for (int i = 0; i < used_args->size(); i++) {
            used_args->at(i)->check_expression(func_defs, params, local_vars);

            // Also check for order, with func_info -- this implicitly does that
            if (i < func->params.size()) {
                if (used_args->at(i)->get_type(func_defs, params, local_vars) != func->params.at(i)->type) {
                    SemanticError *err = new SemanticError;
                    err->line_num = line_num;
                    err->type_error = false;
                    err->msg = "Parameter ";
                    err->msg.append(std::to_string(i));
                    err->msg.append(" of function call on line ");
                    err->msg.append(std::to_string(err->line_num));
                    err->msg.append(" did not have the correct type!");
                    custom_error(err);
                    delete err;
                }
            } else {
                SemanticError *err = new SemanticError;
                err->line_num = line_num;
                err->type_error = false;
                err->msg = "Parameter ";
                err->msg.append(std::to_string(i));
                err->msg.append(" of function call on line ");
                err->msg.append(std::to_string(err->line_num));
                err->msg.append(" was extra, i.e. not included in the function definition!");
                custom_error(err);
                delete err;
            }
        }
        if (used_args->size() < func->params.size()) {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = false;
            err->msg.append("Function call on line ");
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" didn't have enough parameters!");
            custom_error(err);
            delete err;
        }
    } else {
        SemanticError *err = new SemanticError;
        err->line_num = line_num;
        err->type_error = false;
        err->msg = "Function call on line ";
        err->msg.append(std::to_string(err->line_num));
        err->msg.append(" did not have a declared function!");
        custom_error(err);
        delete err;
    }
}

RustishType FuncCallExpressionNode::get_type(FuncSymbolTable *func_defs, VarSymbolTable *params, VarSymbolTable *local_vars) {
    FuncInfo *func = func_defs->lookup(*identifier->identifier);
    if (func != nullptr) {
        if (!func->void_func) {
            type = func->return_type;
            return func->return_type;
        }
        else {
            SemanticError *err = new SemanticError;
            err->line_num = line_num;
            err->type_error = false;
            err->msg = "Function call on line ";
            err->msg.append(std::to_string(err->line_num));
            err->msg.append(" calls a void function, but is used like a value!");
            custom_error(err);
            delete err;
            type = RustishType::i32_t;
            return RustishType::i32_t;
        }
    }
    // Function isn't found - already threw an error
    type = RustishType::i32_t;
    return RustishType::i32_t;
}

IdentifierNode::IdentifierNode(std::string *identifier, int line_num):
    identifier(identifier), line_num(line_num) {};

IdentifierNode::~IdentifierNode() {
    delete identifier;
}

NumberNode::NumberNode(std::string *number, int line_num):
    number(number), line_num(line_num) {};

NumberNode::~NumberNode() {
    delete number;
}

TypeNode::TypeNode(RustishType type):
    type(type) {};

TypeNode::~TypeNode() {};