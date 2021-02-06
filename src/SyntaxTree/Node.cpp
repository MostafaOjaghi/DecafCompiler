//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "Node.h"

#include <utility>

SymbolTable::Scope * SyntaxTree::Node::getScope() {return scope;}

void SyntaxTree::Node::setScope(SymbolTable::Scope *scope) {
    Node::scope = scope;
}

SyntaxTree::Cgen::Cgen(std::string code) : code(std::move(code)) {}
