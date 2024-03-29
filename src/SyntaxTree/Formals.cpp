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

SyntaxTree::Cgen SyntaxTree::Formals::cgen() {
    return Cgen();
}

void SyntaxTree::Formals::handleScope() {
    for (Variable* variable : variables) {
        variable->setScope(this->getScope());
        variable->handleScope();
    }
}

void SyntaxTree::Formals::handleClassHierarchy() {
    for (Variable* variable : variables) {
        variable->handleClassHierarchy();
    }
}
