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
        src/SyntaxTree/ src/SyntaxTree/IfStmt.cpp src/SyntaxTree/IfStmt.h src/SyntaxTree/WhileStmt.cpp src/SyntaxTree/WhileStmt.h src/SyntaxTree/ForStmt.cpp src/SyntaxTree/ForStmt.h src/SyntaxTree/ReturnStmt.cpp src/SyntaxTree/ReturnStmt.h src/SyntaxTree/BreakStmt.cpp src/SyntaxTree/BreakStmt.h src/SyntaxTree/ContinueStmt.cpp src/SyntaxTree/ContinueStmt.h src/SymbolTable/Scope.cpp src/SymbolTable/Scope.h src/SymbolTable/SymbolTableEntry.cpp src/SymbolTable/SymbolTableEntry.h src/SymbolTable/ClassType.cpp src/SymbolTable/ClassType.h src/SyntaxTree/Stmts.cpp src/SyntaxTree/Stmts.h src/SyntaxTree/VariableDecls.cpp src/SyntaxTree/VariableDecls.h src/SyntaxTree/ProgramNode.cpp src/SyntaxTree/ProgramNode.h)
