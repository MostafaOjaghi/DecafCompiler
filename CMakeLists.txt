cmake_minimum_required(VERSION 3.17)
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
        src/SyntaxTree/)
