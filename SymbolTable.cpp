#include <unordered_map>
#include <iostream>
#include <string>

#include "SymbolTable.h"

VarSymbolTable::VarSymbolTable(std::string name) {
    VarSymbolTable::name = name;
    VarSymbolTable::map = std::unordered_map<std::string, VariableInfo *> {};
}

std::string VarSymbolTable::get_name() {
    return VarSymbolTable::name;
}

int VarSymbolTable::size() {
    return VarSymbolTable::map.size();
}

VariableInfo* VarSymbolTable::lookup(std::string key) {
    if (VarSymbolTable::map.count(key) > 0) {
        return VarSymbolTable::map.at(key);
    } else {
        return nullptr;
    }
}

bool VarSymbolTable::insert(std::string key, VariableInfo *value) {
    if (VarSymbolTable::map.count(key) < 1) {
        VarSymbolTable::map.insert(std::make_pair(key, value));
        return true;
    } else {
        std::cout << "Error: variable " << value->name << " on line " << value->line_num << " was declared twice!\n";
        return false;
    }
}

void VarSymbolTable::show() {
    for (auto& [key, value]: VarSymbolTable::map) { // This is wild, works tho - neat feature but very strange - ty stackoverflow, https://stackoverflow.com/questions/50870951/iterating-over-unordered-map-c
        std::cout << "Key " << key << " was " << value << "\n";
    }
}

FuncSymbolTable::FuncSymbolTable(std::string name) {
    FuncSymbolTable::name = name;
    FuncSymbolTable::map = std::unordered_map<std::string, FuncInfo *> {};
}

std::string FuncSymbolTable::get_name() {
    return FuncSymbolTable::name;
}

int FuncSymbolTable::size() {
    return FuncSymbolTable::map.size();
}

FuncInfo* FuncSymbolTable::lookup(std::string key) {
    if (FuncSymbolTable::map.count(key) > 0) {
        return FuncSymbolTable::map.at(key);
    } else {
        return nullptr;
    }
}

bool FuncSymbolTable::insert(std::string key, FuncInfo *value) {
    if (FuncSymbolTable::map.count(key) < 1) {
        FuncSymbolTable::map.insert(std::make_pair(key, value));
        return true;
    } else {
        std::cout << "Error: function " << value->name << " on line " << value->line_num << " was defined twice!\n";
        return false;
    }
}

void FuncSymbolTable::show() {
    for (auto& [key, value]: FuncSymbolTable::map) { // This is wild, works tho - neat feature but very strange - ty stackoverflow, https://stackoverflow.com/questions/50870951/iterating-over-unordered-map-c
        std::cout << "Key " << key << " was " << value << "\n";
    }
}