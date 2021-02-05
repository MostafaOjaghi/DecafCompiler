//
// Created by shengdebao on 2/5/21.
//

#include "Type.h"

const SymbolTable::TypeName &SyntaxTree::Type::getTypeName() const {
    return typeName;
}

void SyntaxTree::Type::setTypeName(const SymbolTable::TypeName &typeName) {
    Type::typeName = typeName;
}

std::string SyntaxTree::Type::cgen() {
    return std::string();
}
