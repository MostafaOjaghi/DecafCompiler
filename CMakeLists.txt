cmake_minimum_required(VERSION 3.17)
project(DecafCompiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SyntaxTree)

add_executable(DecafCompiler
        src/SyntaxTree/Expr.cpp
        src/SyntaxTree/Expr.h
        src/SyntaxTree/Node.cpp
        src/SyntaxTree/Node.h
        src/SyntaxTree/SyntaxTree.h
        src/SyntaxTree/Type.cpp
        src/SyntaxTree/Type.h
        src/lex.yy.c
        src/lex.yy.h
        src/main.cpp
        src/parser.tab.c
        src/parser.tab.h src/SyntaxTree/Decl.cpp src/SyntaxTree/Decl.h src/SyntaxTree/PrintStmt.cpp src/SyntaxTree/PrintStmt.h)
