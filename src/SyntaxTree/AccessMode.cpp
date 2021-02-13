//
// Created by shengdebao on 2/5/21.
//

#include "AccessMode.h"

SymbolTable::AccessMode SyntaxTree::AccessMode::getAccessMode() const {
    return accessMode;
}

void SyntaxTree::AccessMode::setAccessMode(SymbolTable::AccessMode accessMode) {
    AccessMode::accessMode = accessMode;
}

void SyntaxTree::AccessMode::handleScope() {
    // nothing to do!
}
