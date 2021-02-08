cmake_minimum_required(VERSION 3.16)
project(DecafCompiler)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/SyntaxTree)

add_executable(DecafCompiler
        src/SymbolTable/
        src/lex.yy.cpp
        src/lex.yy.h
        src/main.cpp
        src/parser.tab.cpp
        src/parser.tab.h
        src/SyntaxTree/ src/SyntaxTree/IfStmt.cpp src/SyntaxTree/IfStmt.h src/SyntaxTree/WhileStmt.cpp src/SyntaxTree/WhileStmt.h src/SyntaxTree/ForStmt.cpp src/SyntaxTree/ForStmt.h src/SyntaxTree/ReturnStmt.cpp src/SyntaxTree/ReturnStmt.h src/SyntaxTree/BreakStmt.cpp src/SyntaxTree/BreakStmt.h src/SyntaxTree/ContinueStmt.cpp src/SyntaxTree/ContinueStmt.h src/SymbolTable/Scope.cpp src/SymbolTable/Scope.h src/SymbolTable/SymbolTableEntry.cpp src/SymbolTable/SymbolTableEntry.h src/SymbolTable/ClassType.cpp src/SymbolTable/ClassType.h src/SyntaxTree/Stmts.cpp src/SyntaxTree/Stmts.h src/SyntaxTree/VariableDecls.cpp src/SyntaxTree/VariableDecls.h src/SyntaxTree/ProgramNode.cpp src/SyntaxTree/ProgramNode.h src/SyntaxTree/ClassDecl.cpp src/SyntaxTree/ClassDecl.h src/SyntaxTree/InterfaceDecl.cpp src/SyntaxTree/InterfaceDecl.h src/SyntaxTree/Extends.cpp src/SyntaxTree/Extends.h src/SyntaxTree/Implements.cpp src/SyntaxTree/Implements.h src/SyntaxTree/Fields.cpp src/SyntaxTree/Fields.h src/SyntaxTree/Field.cpp src/SyntaxTree/Field.h src/SyntaxTree/AccessMode.cpp src/SyntaxTree/AccessMode.h src/SyntaxTree/Prototypes.cpp src/SyntaxTree/Prototypes.h src/SyntaxTree/Prototype.cpp src/SyntaxTree/Prototype.h src/SyntaxTree/LValue.cpp src/SyntaxTree/LValue.h src/SyntaxTree/Constant.cpp src/SyntaxTree/Constant.h src/SyntaxTree/Call.cpp src/SyntaxTree/Call.h src/SyntaxTree/Actuals.cpp src/SyntaxTree/Actuals.h src/SyntaxTree/Token.cpp src/SyntaxTree/Token.h src/SymbolTable/UniqueGenerator.cpp src/SymbolTable/UniqueGenerator.h)

