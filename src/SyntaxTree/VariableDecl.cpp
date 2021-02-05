//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecl.h"

std::string SyntaxTree::VariableDecl::cgen() {
    return std::string();
}

SyntaxTree::Variable *SyntaxTree::VariableDecl::getVariable() const {
    return variable;
}

void SyntaxTree::VariableDecl::setVariable(SyntaxTree::Variable *variable) {
    VariableDecl::variable = variable;
}
