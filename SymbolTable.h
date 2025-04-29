#include <unordered_map>
#include <string>
#include <vector>

// SymbolTable will be included everywhere, so this will get spread around
typedef struct {
    int line_num;
    bool type_error; // True if type error, false if symbol just doesn't exist in the given tables
    std::string msg; // Error message
} SemanticError;

enum class RustishType {
    i32_t,
    bool_t,
    i32array_t,
    boolarray_t
};

typedef struct {
    std::string name;
    RustishType type;
    int stack_offset;
    bool initialized;
    int line_num;
    int size;
    int arr_len; // If applicable!
} VariableInfo;

typedef struct {
    std::string name;
    std::vector<VariableInfo *> params;
    RustishType return_type;
    bool void_func; // Check this first when checking return type
    int line_num;
} FuncInfo;

class VarSymbolTable {
public:
    std::unordered_map<std::string, VariableInfo *> map;
    std::string name;

    VarSymbolTable(std::string name); // Constructor, create empty map and update name

    std::string get_name(); // Returns the name of this symbol table

    bool insert(std::string key, VariableInfo *value); // Insert a key-value pair into the table, return true if successful (i.e. if the key is not already in the table)

    VariableInfo* lookup(std::string key); // Find the value at this key, return nullptr if it doesn't exist

    int size(); // Just returns the number of pairs in the table

    void show(); // Output the contents of the table in a nice fashion
};

class FuncSymbolTable {
public:
    std::unordered_map<std::string, FuncInfo *> map;
    std::string name;

    FuncSymbolTable(std::string name); // Constructor, create empty map and update name

    std::string get_name(); // Returns the name of this symbol table

    bool insert(std::string key, FuncInfo *value); // Insert a key-value pair into the table, return true if successful (i.e. if the key is not already in the table)

    FuncInfo* lookup(std::string key); // Find the value at this key, return nullptr if it doesn't exist

    int size(); // Just returns the number of pairs in the table

    void show(); // Output the contents of the table in a nice fashion
};