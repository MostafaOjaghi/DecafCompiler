//
// Created by shengdebao on 2/5/21.
//

#include <string>
#include "Variable.h"

SyntaxTree::Cgen SyntaxTree::Variable::cgen() {
    return Cgen();
}

SyntaxTree::Type *SyntaxTree::Variable::getType() const {
    return type;
}

void SyntaxTree::Variable::setType(Type *type) {
    Variable::type = type;
}

const std::string &SyntaxTree::Variable::getId() const {
    return id;
}

void SyntaxTree::Variable::setId(const std::string &id) {
    Variable::id = id;
}

void SyntaxTree::Variable::handleScope() {
    SymbolTable::TypeName typeName = SymbolTable::TypeName(this->getType()->getTypeNameId(), this->getType()->getDimension());
    SymbolTable::SymbolTableEntry *entry = new SymbolTable::SymbolTableEntry(typeName);
    this->getScope()->addEntry(this->getId(), entry);
}
