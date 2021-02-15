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

void SyntaxTree::DeclToVariableDecl::handleClassHierarchy() {
    this->getVariableDecl()->handleClassHierarchy();
}

SyntaxTree::FunctionDecl *SyntaxTree::DeclToFunctionDecl::getFunctionDecl() const {
    return functionDecl;
}

void SyntaxTree::DeclToFunctionDecl::setFunctionDecl(SyntaxTree::FunctionDecl *functionDecl) {
    DeclToFunctionDecl::functionDecl = functionDecl;
}

SyntaxTree::Cgen SyntaxTree::DeclToFunctionDecl::cgen() {
    return functionDecl->cgen();
}

// handling scope
void SyntaxTree::DeclToFunctionDecl::handleScope() {
    this->getFunctionDecl()->setScope(this->getScope());
    this->getFunctionDecl()->handleScope();
}

void SyntaxTree::DeclToFunctionDecl::handleClassHierarchy() {
    this->getFunctionDecl()->handleClassHierarchy();
}

SyntaxTree::ClassDecl *SyntaxTree::DeclToClassDecl::getClassDecl() const {
    return classDecl;
}

void SyntaxTree::DeclToClassDecl::setClassDecl(SyntaxTree::ClassDecl *classDecl) {
    DeclToClassDecl::classDecl = classDecl;
}

void SyntaxTree::DeclToClassDecl::handleScope() {
    std::string classId = this->getClassDecl()->getId();
    SymbolTable::ClassType::addType(new SymbolTable::ClassType(classId));
    auto newScope = new SymbolTable::Scope(classId);
    newScope->setIsClass(true);
    this->getClassDecl()->setScope(newScope);
    this->getClassDecl()->handleScope();
    if (this->getClassDecl()->getExtends()->getParentClassId().empty())
        this->getClassDecl()->getScope()->setPar(this->getScope());
}

void SyntaxTree::DeclToClassDecl::handleClassHierarchy() {
    this->getClassDecl()->handleClassHierarchy();
}

SyntaxTree::Cgen SyntaxTree::DeclToClassDecl::cgen() {
    return classDecl->cgen();
}

SyntaxTree::InterfaceDecl *SyntaxTree::DeclToInterfaceDecl::getInterfaceDecl() const {
    return interfaceDecl;
}

void SyntaxTree::DeclToInterfaceDecl::setInterfaceDecl(SyntaxTree::InterfaceDecl *interfaceDecl) {
    DeclToInterfaceDecl::interfaceDecl = interfaceDecl;
}

void SyntaxTree::DeclToInterfaceDecl::handleClassHierarchy() {
    this->getInterfaceDecl()->handleClassHierarchy();
}
