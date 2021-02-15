//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "TypeName.h"
#include <iostream>
#include <utility>

extern FILE *output_file;

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

bool SymbolTable::TypeName::isArray() const {
    return dimension > 0;
}

void SymbolTable::TypeName::semanticError() {
    std::cout << "semantic ERROR!" << std::endl;
    char semantic_error_code[] = ".text\n"
                                 ".globl main\n"
                                 "\n"
                                 "main:\n"
                                 "la $a0 , errorMsg\n"
                                 "addi $v0 , $zero, 4\n"
                                 "syscall\n"
                                 "jr $ra\n"
                                 "\n"
                                 ".data\n"
                                 "errorMsg: .asciiz \"Semantic Error\"";
    fprintf(output_file, "%s", semantic_error_code);
    fclose(output_file);
    exit(0);
}

bool SymbolTable::TypeName::checkCastable(SymbolTable::TypeName from, SymbolTable::TypeName to) {
    if (from.isPrimitive() || to.isPrimitive()) {
        return from.getId() == to.getId();
    }

    SymbolTable::ClassType *classTypeFrom = from.getClassType();
    SymbolTable::ClassType *classTypeTo = to.getClassType();
    while (classTypeFrom != nullptr && classTypeFrom != classTypeTo) {
        classTypeFrom = classTypeFrom->getParent();
    }
    return classTypeFrom == classTypeTo;
}
