# Flags and stuff from Halterman

#CC = g++     
#OP = # -O2      # no optimizations for now
#FLAGS = -g -std=c++20 # -Wall -Wextra -Wpedantic -Wno-unused-function -Wno-unused-parameter 
#
#all ASTtree: lexer.cpp parser.cpp SymbolTable.o ASTtree.cpp
#	$(CC) $(OP) $(FLAGS) $^ -o ASTtree
#
#lexer.hpp lexer.cpp: rustish_lex_file.l
#	flex --header-file=lexer.hpp -o lexer.cpp rustish_lex_file.l
#
#parser.hpp parser.cpp: rustish_parser_file.y
#	bison -d -v -o parser.cpp rustish_parser_file.y -Wcounterexamples
#
#SymbolTable.o: SymbolTable.cpp
#	$(CC) $(OP) $(FLAGS) $^ -c SymbolTable.cpp
#
#clean:
#	rm parser.output lexer.cpp lexer.hpp parser.cpp parser.hpp ASTtree
#
#run: ASTtree
#	./ASTtree test.ri
#
#debug: rustish
#	gdb ./rustish test.ri


CC = g++     
OP = # -O2      # no optimizations for now
FLAGS = -g -std=c++20 #-Wall -Wextra -Wpedantic -Wno-unused-function -Wno-unused-parameter -std=c++20

all: rustish

rustish: parse.tab.o lex.yy.o SymbolTable.o ASTtree.o
	${CC} ${OP} ${FLAGS} -o rustish parse.tab.o lex.yy.o ASTtree.o SymbolTable.o

ASTtree.o: ASTtree.cpp ASTtree.h
	${CC} ${OP} ${FLAGS} -c ASTtree.cpp

#rustish.tab.cpp: rustish.tab.c
#	mv -f rustish.tab.c rustish.tab.cpp

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
