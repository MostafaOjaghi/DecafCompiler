//
// Created by shengdebao on 2/5/21.
//

#include "Extends.h"

const std::string &SyntaxTree::Extends::getParentClassId() const {
    return parentClassId;
}

void SyntaxTree::Extends::setParentClassId(const std::string &parentClassId) {
    Extends::parentClassId = parentClassId;
}
