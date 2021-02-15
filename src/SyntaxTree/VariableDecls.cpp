//
// Created by shengdebao on 2/5/21.
//

#include "VariableDecls.h"

const std::vector<SyntaxTree::VariableDecl *> &SyntaxTree::VariableDecls::getVariableDecls() const {
    return variableDecls;
}

SyntaxTree::Cgen SyntaxTree::VariableDecls::cgen() {
    Cgen cgen;
    for (VariableDecl *decl : variableDecls) {
        cgen.append(decl->cgen());
    }
    return cgen;
}

void SyntaxTree::VariableDecls::addVariableDecl(SyntaxTree::VariableDecl *variableDecl) {
    variableDecls.push_back(variableDecl);
}

void SyntaxTree::VariableDecls::handleScope() {
    for (VariableDecl *variableDecl : variableDecls) {
        variableDecl->setScope(this->getScope());
        variableDecl->handleScope();
    }
}

void SyntaxTree::VariableDecls::handleClassHierarchy() {
    for (VariableDecl *variableDecl : variableDecls)  {
        variableDecl->handleClassHierarchy();
    }
}
