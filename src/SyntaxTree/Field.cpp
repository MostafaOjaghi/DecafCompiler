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
