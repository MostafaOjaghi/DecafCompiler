//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecl.h"

SyntaxTree::Cgen SyntaxTree::VariableDecl::cgen() {
    std::string typenameId = this->getVariable()->getType()->getTypeNameId();
    if (typenameId != "double") {
        Cgen cgen("Assign " + getScope()->getEntry(variable->getId())->getUniqueId() + " = 0\n");
        cgen.var_count = 1;
        return cgen;
    }
    Cgen cgen("AssignF " + getScope()->getEntry(variable->getId())->getUniqueId() + " = 0.0\n");
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

void SyntaxTree::VariableDecl::handleClassHierarchy() {
    this->getVariable()->handleClassHierarchy();
}
