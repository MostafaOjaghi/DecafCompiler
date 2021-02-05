# NOTE1: You can use wildcards in dependencies and g++ command.
# NOTE2: main should depend on all headers and code files. (*.h and *.cpp if you have multiple files)
all: ../main

../main: lex.yy.c lex.yy.h **/*.cpp **/*.h *.cpp parser.tab.c parser.tab.h
	g++ -std=c++14 -I . lex.yy.c **/*.cpp *.cpp parser.tab.c -o ../main

lex.yy.c lex.yy.h: scanner.l parser.tab.h
	flex scanner.l

parser.tab.c parser.tab.h: parser.y
	bison -d -r all parser.y

clean:
	rm ../main lex.yy.c lex.yy.h parser.tab.c parser.tab.h
