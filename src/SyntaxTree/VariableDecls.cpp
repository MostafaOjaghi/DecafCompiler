//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecls.h"

const std::vector<SyntaxTree::VariableDecl *> &SyntaxTree::VariableDecls::getVariableDecls() const {
    return variableDecls;
}

void SyntaxTree::VariableDecls::addVariableDecl(SyntaxTree::VariableDecl *variableDecl) {
    variableDecls.push_back(variableDecl);
}
