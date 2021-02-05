//
// Created by shengdebao on 2/5/21.
//

#include "SymbolTableEntry.h"

const SymbolTable::TypeName &SymbolTable::SymbolTableEntry::getTypeName() const {
    return typeName;
}

void SymbolTable::SymbolTableEntry::setTypeName(const SymbolTable::TypeName &typeName) {
    SymbolTableEntry::typeName = typeName;
}
