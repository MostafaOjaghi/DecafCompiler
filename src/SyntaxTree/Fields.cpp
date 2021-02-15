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

void SyntaxTree::Fields::handleScope() {
    for (Field *field: fields) {
        field->setScope(this->getScope());
        field->handleScope();
    }
}

SyntaxTree::Cgen SyntaxTree::Fields::cgen() {
    Cgen cgen;
    for (Field *field : fields)
        cgen.append(field->cgen());
    return cgen;
}
