//
// Created by shengdebao on 2/5/21.
//

#include "Formals.h"

void SyntaxTree::Formals::addVariable(Variable *variable) {
    variables.push_back(variable);
}

const std::vector<SyntaxTree::Variable *> &SyntaxTree::Formals::getVariables() const {
    return variables;
}

std::string SyntaxTree::Formals::cgen() {
    return std::string();
}
