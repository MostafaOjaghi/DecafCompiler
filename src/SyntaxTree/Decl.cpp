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

void SyntaxTree::DeclToVariableDecl::handleScope() {
    this->getVariableDecl()->setScope(this->getScope());
    this->getVariableDecl()->handleScope();
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

// handling scope
void SyntaxTree::DeclToFunctionDecl::handleScope() {
    this->getFunctionDecl()->setScope(this->getScope());
    this->getFunctionDecl()->handleScope();
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
