//
// Created by shengdebao on 2/5/21.
//

#include "Field.h"

SyntaxTree::AccessMode *SyntaxTree::FieldToVariableDecl::getAccessMode() const {
    return accessMode;
}

void SyntaxTree::FieldToVariableDecl::setAccessMode(SyntaxTree::AccessMode *accessMode) {
    FieldToVariableDecl::accessMode = accessMode;
}

SyntaxTree::VariableDecl *SyntaxTree::FieldToVariableDecl::getVariableDecl() const {
    return variableDecl;
}

void SyntaxTree::FieldToVariableDecl::setVariableDecl(SyntaxTree::VariableDecl *variableDecl) {
    FieldToVariableDecl::variableDecl = variableDecl;
}

void SyntaxTree::FieldToVariableDecl::handleScope() {
    this->getAccessMode()->setScope(this->getScope());
    this->getAccessMode()->handleScope();
    SymbolTable::AccessMode accessMode1 = this->getAccessMode()->getAccessMode();
    this->getVariableDecl()->setScope(this->getScope());
    this->getVariableDecl()->handleScope();
    SymbolTable::SymbolTableEntry *entry = this->getVariableDecl()->getVariable()->getScope()->getVariable(
            this->getVariableDecl()->getVariable()->getId());
    entry->setAccessMode(accessMode1);
}

void SyntaxTree::FieldToVariableDecl::handleClassHierarchy() {
    this->getVariableDecl()->handleClassHierarchy();
    this->getAccessMode()->handleClassHierarchy();
}

SyntaxTree::AccessMode *SyntaxTree::FieldToFunctionDecl::getAccessMode() const {
    return accessMode;
}

void SyntaxTree::FieldToFunctionDecl::setAccessMode(SyntaxTree::AccessMode *accessMode) {
    FieldToFunctionDecl::accessMode = accessMode;
}

SyntaxTree::FunctionDecl *SyntaxTree::FieldToFunctionDecl::getFunctionDecl() const {
    return functionDecl;
}

void SyntaxTree::FieldToFunctionDecl::setFunctionDecl(SyntaxTree::FunctionDecl *functionDecl) {
    FieldToFunctionDecl::functionDecl = functionDecl;
}

SyntaxTree::Cgen SyntaxTree::FieldToFunctionDecl::cgen() {
    return functionDecl->cgen();
}

void SyntaxTree::FieldToFunctionDecl::handleScope() {
    this->getAccessMode()->setScope(this->getScope());
    this->getAccessMode()->handleScope();
    SymbolTable::AccessMode accessMode1 = this->getAccessMode()->getAccessMode();
    this->getFunctionDecl()->setScope(this->getScope());
    this->getFunctionDecl()->handleScope();
    SymbolTable::SymbolTableEntry *entry = this->getFunctionDecl()->getScope()->getFunction(
            this->getFunctionDecl()->getFunctionIdentifier());
    entry->setAccessMode(accessMode1);
}

void SyntaxTree::FieldToFunctionDecl::handleClassHierarchy() {
    this->getAccessMode()->handleClassHierarchy();
    this->getFunctionDecl()->handleClassHierarchy();
}
