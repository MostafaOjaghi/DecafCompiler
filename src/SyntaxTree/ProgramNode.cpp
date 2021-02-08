//
// Created by mostafa on 2/5/21.
//

#include <iostream>
#include "ProgramNode.h"

#include "Decl.h"

void SyntaxTree::ProgramNode::addDecl(Decl *decl) {
    declerations.push_back(decl);
}

SyntaxTree::Cgen SyntaxTree::ProgramNode::cgen() {
    std::string variables;
    std::string text;
    Cgen cgen;
    for (Decl *decl : declerations) {
        if (dynamic_cast<DeclToVariableDecl *>(decl))
            variables += decl->cgen().code;
        else
            text += decl->cgen().code;
    }
    cgen.code = variables +
            "LCall main\n" +
            "Exit\n" +
            text;
    return cgen;
}

void SyntaxTree::ProgramNode::handleScope() {
    this->setScope(new SymbolTable::Scope("", nullptr));
    for (Decl *decl : declerations) {
        if (DeclToVariableDecl *node = dynamic_cast<DeclToVariableDecl *>(decl)) {
            node->setScope(this->getScope());
            node->handleScope();

        } else if (DeclToFunctionDecl * node = dynamic_cast<DeclToFunctionDecl *>(decl)) {
            std::string functionIdent = node->getFunctionDecl()->getFunctionIdentifier();
            node->setScope(new SymbolTable::Scope(functionIdent, this->getScope()));
            node->handleScope();

        } else if (DeclToClassDecl * node = dynamic_cast<DeclToClassDecl *>(decl)) {
            // TODO: class declaration scope setting should be completed
        } else if (DeclToInterfaceDecl * node = dynamic_cast<DeclToInterfaceDecl *>(decl)) {
            // TODO: interface declaration scope setting should be completed
        } else {
            assert(0);
        }
    }
}
