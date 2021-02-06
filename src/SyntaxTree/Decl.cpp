//
// Created by shengdebao on 2/5/21.
//

#include "Decl.h"

SyntaxTree::VariableDecl *SyntaxTree::DeclToVariableDecl::getVariableDecl() const {
    return variableDecl;
}

void SyntaxTree::DeclToVariableDecl::setVariableDecl(SyntaxTree::VariableDecl *variableDecl) {
    DeclToVariableDecl::variableDecl = variableDecl;
}

SyntaxTree::Cgen SyntaxTree::DeclToVariableDecl::cgen() {
    return variableDecl->cgen();
}

SyntaxTree::FunctionDecl *SyntaxTree::DeclToFunctionDecl::getFunctionDecl() const {
    return functionDecl;
}

void SyntaxTree::DeclToFunctionDecl::setFunctionDecl(SyntaxTree::FunctionDecl *functionDecl) {
    DeclToFunctionDecl::functionDecl = functionDecl;
}

SyntaxTree::Cgen SyntaxTree::DeclToFunctionDecl::cgen() {
    return Cgen();
}

SyntaxTree::ClassDecl *SyntaxTree::DeclToClassDecl::getClassDecl() const {
    return classDecl;
}

void SyntaxTree::DeclToClassDecl::setClassDecl(SyntaxTree::ClassDecl *classDecl) {
    DeclToClassDecl::classDecl = classDecl;
}

SyntaxTree::InterfaceDecl *SyntaxTree::DeclToInterfaceDecl::getInterfaceDecl() const {
    return interfaceDecl;
}

void SyntaxTree::DeclToInterfaceDecl::setInterfaceDecl(SyntaxTree::InterfaceDecl *interfaceDecl) {
    DeclToInterfaceDecl::interfaceDecl = interfaceDecl;
}
