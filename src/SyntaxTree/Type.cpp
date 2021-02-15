//
// Created by shengdebao on 2/5/21.
//

#include "Type.h"


const std::string &SyntaxTree::Type::getTypeNameId() const {
    return typeNameID;
}


SyntaxTree::Cgen SyntaxTree::Type::cgen() {
    return Cgen();
}

void SyntaxTree::Type::setTypeNameId(const std::string &typeNameId) {
    typeNameID = typeNameId;
}

int SyntaxTree::Type::getDimension() const {
    return dimension;
}

void SyntaxTree::Type::setDimension(int dimension) {
    Type::dimension = dimension;
}

void SyntaxTree::Type::incrementDimension() {
    Type::dimension++;
}

SymbolTable::TypeName SyntaxTree::Type::getTypeName() {
    return SymbolTable::TypeName(typeNameID, dimension);
}

void SyntaxTree::Type::handleClassHierarchy() {
    // nothing to do
}
