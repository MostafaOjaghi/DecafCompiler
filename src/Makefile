# NOTE1: You can use wildcards in dependencies and g++ command.
# NOTE2: main should depend on all headers and code files. (*.h and *.cpp if you have multiple files)
all: ../main

../main: lex.yy.cpp lex.yy.h **/*.cpp **/*.h *.cpp parser.tab.cpp parser.tab.h
	clang++ -std=c++14 -I . **/*.cpp *.cpp -o ../main

lex.yy.cpp lex.yy.h: scanner.l parser.tab.h
	flex scanner.l

parser.tab.cpp parser.tab.h: parser.y
	bison parser.y -o parser.tab.cpp --defines=parser.tab.h -r all

clean:
	rm ../main lex.yy.cpp lex.yy.h parser.tab.cpp parser.tab.h
