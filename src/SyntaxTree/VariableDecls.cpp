//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecls.h"

const std::vector<SyntaxTree::VariableDecl *> &SyntaxTree::VariableDecls::getVariableDecls() const {
    return variableDecls;
}

SyntaxTree::Cgen SyntaxTree::VariableDecls::cgen() {
    return Cgen();
}

void SyntaxTree::VariableDecls::addVariableDecl(SyntaxTree::VariableDecl *variableDecl) {
    variableDecls.push_back(variableDecl);
}

void SyntaxTree::VariableDecls::handleScope() {
    for (VariableDecl *variableDecl : variableDecls) {
        this->setScope(this->getScope());
        this->handleScope();
    }
}
