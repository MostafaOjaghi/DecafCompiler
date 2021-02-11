//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecl.h"

SyntaxTree::Cgen SyntaxTree::VariableDecl::cgen() {
    Cgen cgen("Assign " + getScope()->getEntry(variable->getId())->getUniqueId() + " = 0\n");
    cgen.var_count = 1;
    return cgen;
}

SyntaxTree::Variable *SyntaxTree::VariableDecl::getVariable() const {
    return variable;
}

void SyntaxTree::VariableDecl::setVariable(SyntaxTree::Variable *variable) {
    VariableDecl::variable = variable;
}

void SyntaxTree::VariableDecl::handleScope() {
    this->getVariable()->setScope(this->getScope());
    this->getVariable()->handleScope();
}
