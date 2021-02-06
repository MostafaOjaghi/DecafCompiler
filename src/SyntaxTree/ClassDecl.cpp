//
// Created by shengdebao on 2/5/21.
//

#include "ClassDecl.h"

SyntaxTree::Extends *SyntaxTree::ClassDecl::getExtends() const {
    return extends;
}

void SyntaxTree::ClassDecl::setExtends(SyntaxTree::Extends *extends) {
    ClassDecl::extends = extends;
}

SyntaxTree::Implements *SyntaxTree::ClassDecl::getImplements() const {
    return implements;
}

void SyntaxTree::ClassDecl::setImplements(SyntaxTree::Implements *implements) {
    ClassDecl::implements = implements;
}

SyntaxTree::Fields *SyntaxTree::ClassDecl::getFields() const {
    return fields;
}

void SyntaxTree::ClassDecl::setFields(SyntaxTree::Fields *fields) {
    ClassDecl::fields = fields;
}
