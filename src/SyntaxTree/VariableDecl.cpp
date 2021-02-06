//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecl.h"

SyntaxTree::Cgen SyntaxTree::VariableDecl::cgen() {
    return Cgen("Assign " + variable->getId() + " 0\n");
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
