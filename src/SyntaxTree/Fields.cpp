//
// Created by shengdebao on 2/5/21.
//

#include "Fields.h"

const std::vector<SyntaxTree::Field *> &SyntaxTree::Fields::getFields() const {
    return fields;
}

void SyntaxTree::Fields::addField(SyntaxTree::Field *field) {
    fields.push_back(field);
}
