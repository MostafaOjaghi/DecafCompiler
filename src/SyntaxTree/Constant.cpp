//
// Created by shengdebao on 2/5/21.
//

#include "Constant.h"

const std::string &SyntaxTree::Constant::getConstantIdType() const {
    return constantIdType;
}

void SyntaxTree::Constant::setConstantIdType(const std::string &constantIdType) {
    Constant::constantIdType = constantIdType;
}

const std::string &SyntaxTree::Constant::getConstantValue() const {
    return constantValue;
}

void SyntaxTree::Constant::setConstantValue(const std::string &constantValue) {
    Constant::constantValue = constantValue;
}
