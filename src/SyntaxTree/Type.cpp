//
// Created by shengdebao on 2/5/21.
//

#include "Type.h"


std::string SyntaxTree::Type::cgen() {
    return std::string();
}

const std::string &SyntaxTree::Type::getTypeNameId() const {
    return typeNameID;
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
