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

const std::string &SyntaxTree::ClassDecl::getId() const {
    return Id;
}

void SyntaxTree::ClassDecl::setId(const std::string &id) {
    Id = id;
}

void SyntaxTree::ClassDecl::handleScope() {
    this->getExtends()->setScope(this->getScope());
    this->getExtends()->handleScope();

    auto *classType = new SymbolTable::ClassType(this->getId());
    classType->setScope(this->getScope());
    SymbolTable::ClassType::addType(classType);
    classType->setParentName(this->getExtends()->getParentClassId());

    for (auto f : this->getFields()->getFields()) {
        if (FieldToVariableDecl *node = dynamic_cast<FieldToVariableDecl *>(f)) {
            classType->addToLayout(node->getVariableDecl()->getVariable()->getId());
        } else if (FieldToFunctionDecl *node = dynamic_cast<FieldToFunctionDecl *>(f)) {
            // TODO: complete class methods
            assert(0);
        }
    }
    this->getImplements()->setScope(this->getScope());
    this->getImplements()->handleScope();
    this->getFields()->setScope(this->getScope());
    this->getFields()->handleScope();
}

void SyntaxTree::ClassDecl::handleClassHierarchy() {
    SymbolTable::ClassType::getClass(this->getId())->handleHierarchy();
}
