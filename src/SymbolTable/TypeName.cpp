//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "TypeName.h"

#include <utility>

bool SymbolTable::TypeName::isPrimitive() const {
    return classType == nullptr;
}

const std::string &SymbolTable::TypeName::getId() const {
    return id;
}

void SymbolTable::TypeName::setId(const std::string &id) {
    TypeName::id = id;
}

SymbolTable::ClassType *SymbolTable::TypeName::getClassType() const {
    return classType;
}

void SymbolTable::TypeName::setClassType(ClassType *classType) {
    TypeName::classType = classType;
}

int SymbolTable::TypeName::getDimension() const {
    return dimension;
}

void SymbolTable::TypeName::setDimension(int dimension) {
    TypeName::dimension = dimension;
}

// TODO: this should get the id if the id is primitive it should set it to a primitive type
//  - and if it is not it should be set to a class type

SymbolTable::TypeName::TypeName(std::string id, int dimension) : id(std::move(id)), dimension(dimension) {}
