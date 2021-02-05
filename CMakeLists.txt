cmake_minimum_required(VERSION 3.16)
project(DecafCompiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SyntaxTree)

add_executable(DecafCompiler
        src/SymbolTable/
        src/lex.yy.c
        src/lex.yy.h
        src/main.cpp
        src/parser.tab.c
        src/parser.tab.h
        src/SyntaxTree/ src/SyntaxTree/IfStmt.cpp src/SyntaxTree/IfStmt.h src/SyntaxTree/WhileStmt.cpp src/SyntaxTree/WhileStmt.h src/SyntaxTree/ForStmt.cpp src/SyntaxTree/ForStmt.h src/SyntaxTree/ReturnStmt.cpp src/SyntaxTree/ReturnStmt.h src/SyntaxTree/BreakStmt.cpp src/SyntaxTree/BreakStmt.h src/SyntaxTree/ContinueStmt.cpp src/SyntaxTree/ContinueStmt.h)
