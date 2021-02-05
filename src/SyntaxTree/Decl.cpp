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

std::string SyntaxTree::DeclToVariableDecl::cgen() {
    return std::string();
}

SyntaxTree::FunctionDecl *SyntaxTree::DeclToFunctionDecl::getFunctionDecl() const {
    return functionDecl;
}

void SyntaxTree::DeclToFunctionDecl::setFunctionDecl(SyntaxTree::FunctionDecl *functionDecl) {
    DeclToFunctionDecl::functionDecl = functionDecl;
}

std::string SyntaxTree::DeclToFunctionDecl::cgen() {
    return std::string();
}
