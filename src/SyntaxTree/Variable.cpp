//
// Created by shengdebao on 2/5/21.
//

#include <string>
#include "Variable.h"

std::string SyntaxTree::Variable::cgen() {
    return std::string();
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
