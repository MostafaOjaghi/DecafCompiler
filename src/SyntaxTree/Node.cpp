//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "Node.h"

#include <utility>

SymbolTable::Scope * SyntaxTree::Node::getScope() {return scope;}

SyntaxTree::Cgen::Cgen(std::string code) : code(std::move(code)) {}
