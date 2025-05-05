/* This is the definition section */

%{
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "parse.tab.hpp"

int unrecognized_words = 0;
int unrecognized_symbols = 0;
int longest_symbol_name = 0;
int error = 0;

typedef struct token {
    int line;
    std::string name;
    std::string value;
} token;

std::vector<token> tokens = {};

void add_token(int line, std::string name, std::string value) {
    token to_add;
    to_add.line = line;
    to_add.name = name;
    if (name.size() > longest_symbol_name) {
        longest_symbol_name = name.size();
    }

    to_add.value = value;
    tokens.push_back(to_add);
    if (unrecognized_words + unrecognized_symbols >= 20) {
        error = 1;
    }
}

%}

%option noyywrap
%option yylineno

digit [0-9]
letter [a-zA-Z]
whitespace [ \t\n:blank:]*
identifier [a-zA-Z_]([a-zA-Z]|[0-9]|_)*


%% /* Rules Section */

"//".* { /* Rule to detect comments! Detects the slashes and then eats anything after */
    // Do nothing :)
}

[ \t\n] { /* Rule to detect whitespace */
    // Eats whitespace
}

"fn" {
    add_token(yylineno, "FN", "");
    return FN;
}

"main" {
    add_token(yylineno, "MAIN", "");
    return MAIN;
}

"(" {
    add_token(yylineno, "LPAREN", "");
    return LPAREN;
}

")" {
    add_token(yylineno, "RPAREN", "");
    return RPAREN;
}

"{" {
    add_token(yylineno, "LCURLY", "");
    return LCURLY;
}

"}" {
    add_token(yylineno, "RCURLY", "");
    return RCURLY;
}

"[" {
    add_token(yylineno, "LSQUARE", "");
    return LSQUARE;
}

"]" {
    add_token(yylineno, "RSQUARE", "");
    return RSQUARE;
}

"println" {
    add_token(yylineno, "PRINTLN", "");
    return PRINTLN;
}

"let" {
    add_token(yylineno, "LET", "");
    return LET;
}

"mut" {
    add_token(yylineno, "MUT", "");
    return MUT;
}

":" {
    add_token(yylineno, "COLON", "");
    return COLON;
}

"i32" {
    add_token(yylineno, "I32", "");
    return I32;
}

"bool" {
    add_token(yylineno, "BOOL", "");
    return BOOL;
}

";" {
    add_token(yylineno, "SEMI", "");
    return SEMICOLON;
}

"=" {
    add_token(yylineno, "ASSIGN", "");
    return ASSIGN;
}

"print" {
    add_token(yylineno, "PRINT", "");
    return PRINT;
}

"==" {
    add_token(yylineno, "EQ", "");
    return EQ;
}

"!=" {
    add_token(yylineno, "NE", "");
    return NE;
}

"if" {
    add_token(yylineno, "IF", "");
    return IF;
}

"," {
    add_token(yylineno, "COMMA", "");
    return COMMA;
}

"else" {
    add_token(yylineno, "ELSE", "");
    return ELSE;
}

"while" {
    add_token(yylineno, "WHILE", "");
    return WHILE;
}

"read" {
    add_token(yylineno, "READ", "");
    return READ;
}

(0|[1-9][0-9]*) {
    add_token(yylineno, "NUMBER", yytext);
    yylval.token = (TokenData*) malloc(sizeof(TokenData));
    yylval.token->value = yytext;
    return NUMBER;
}

"\." {
    add_token(yylineno, "DOT", "");
    return DOT;
}

"len" {
    add_token(yylineno, "LEN", "");
    return LEN;
}

"-" {
    add_token(yylineno, "SUB", "");
    return MINUS;
}

"+" {
    add_token(yylineno, "ADD", "");
    return PLUS;
}

"%" {
    add_token(yylineno, "MOD", "");
    return MOD;
}

"\*" {
    add_token(yylineno, "TIMES", "");
    return TIMES;
}

"/" {
    add_token(yylineno, "DIV", "");
    return DIV;
}

"&&" {
    add_token(yylineno, "AND", "");
    return AND;
}

"||" {
    add_token(yylineno, "OR", "");
    return OR;
}

">=" {
    add_token(yylineno, "GE", "");
    return GE;
}

"<=" {
    add_token(yylineno, "LE", "");
    return LE;
}

">" {
    add_token(yylineno, "GT", "");
    return GT;
}

"<" {
    add_token(yylineno, "LT", "");
    return LT;
}

"->" {
    add_token(yylineno, "ARROW", "");
    return ARROW;
}

"true" {
    add_token(yylineno, "TRUE", "");
    return TRUE;
}

"false" {
    add_token(yylineno, "FALSE", "");
    return FALSE;
}

"return" {
    add_token(yylineno, "RETURN", "");
    return RETURN;
}

[a-zA-Z_]([a-zA-Z0-9_])* {
    add_token(yylineno, "IDENTIFIER", yytext);
    yylval.token = (TokenData*) malloc(sizeof(TokenData));
    yylval.token->value = yytext;
    return IDENTIFIER;
}

[^()\[\]{} <>*\/+\-\n\t\r=;:]([a-zA-Z0-9])+ {
    unrecognized_words += 1;
    std::cout << "Error: unrecognized word on line " << yylineno << "\n";
    add_token(yylineno, yytext, "error: unrecognized word");
}

.{0,1} {
    unrecognized_symbols += 1;
    std::cout << "Error: unrecognized symbol on line " << yylineno << "\n";
    add_token(yylineno, yytext, "error: unrecognized symbol");
}

%%

/* Code Section */