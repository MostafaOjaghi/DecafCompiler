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
    Cgen variables;
    Cgen text;
    Cgen cgen;
    for (Decl *decl : declerations) {
        if (dynamic_cast<DeclToVariableDecl *>(decl))
            variables.append(decl->cgen());
        else
            text.append(decl->cgen());
    }
    cgen.append(variables);
    cgen.append("Lcall " + getScope()->getFunction("main")->getUniqueId() + "\n" +
                "Exit\n");
    cgen.append(text);
    return cgen;
}

void SyntaxTree::ProgramNode::handleScope() {
    this->setScope(new SymbolTable::Scope("global", nullptr));
    for (Decl *decl : declerations) {
        if (DeclToVariableDecl *node = dynamic_cast<DeclToVariableDecl *>(decl)) {
            node->setScope(this->getScope());
            node->handleScope();

        } else if (DeclToFunctionDecl * node = dynamic_cast<DeclToFunctionDecl *>(decl)) {
            node->setScope(getScope());
            node->handleScope();

        } else if (DeclToClassDecl * node = dynamic_cast<DeclToClassDecl *>(decl)) {
            node->setScope(this->getScope());
            node->handleScope();
        } else if (DeclToInterfaceDecl * node = dynamic_cast<DeclToInterfaceDecl *>(decl)) {
            // TODO: interface declaration scope setting should be completed
        } else {
            assert(0);
        }
    }
}

void SyntaxTree::ProgramNode::handleClassHierarchy() {
    for (Decl *decl : declerations) {
        if (DeclToClassDecl * node = dynamic_cast<DeclToClassDecl *>(decl)) {
            node->handleClassHierarchy();
        } else if (DeclToVariableDecl * node = dynamic_cast<DeclToVariableDecl *>(decl)) {
            node->handleClassHierarchy();
        } else if (DeclToFunctionDecl * node = dynamic_cast<DeclToFunctionDecl *>(decl)) {
            node->handleClassHierarchy();
        }
    }
}
