# My professor, Dr. Halterman, created a makefile that I based this off of
CC = g++     
OP = # -O2      # no optimizations for now
FLAGS = -g -std=c++20 #-Wall -Wextra -Wpedantic -Wno-unused-function -Wno-unused-parameter -std=c++20

all: rustish

rustish: parse.tab.o lex.yy.o SymbolTable.o ASTtree.o
	${CC} ${OP} ${FLAGS} -o rustish parse.tab.o lex.yy.o ASTtree.o SymbolTable.o

ASTtree.o: ASTtree.cpp ASTtree.h
	${CC} ${OP} ${FLAGS} -c ASTtree.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	${CC} ${OP} ${FLAGS} -c SymbolTable.cpp

lex.yy.o: lex.yy.cpp
	${CC} $(OP) $(FLAGS) -Wno-sign-compare -c lex.yy.cpp 

lex.yy.cpp: rustish_lex_file.l
	flex --header-file=lex.yy.hpp -o lex.yy.cpp rustish_lex_file.l

parse.tab.o: parse.tab.cpp SymbolTable.h
	${CC} ${OP} ${FLAGS} -c parse.tab.cpp

parse.tab.cpp: rustish_parser_file.y
	bison -Wcounterexamples -v -d -o parse.tab.cpp rustish_parser_file.y

clean:
	/bin/rm -f *.o *.yy.c *.yy.cpp *.tab.cpp *.tab.c *.tab.hpp \
	           core *.output *.temp *~ calc *.asm
