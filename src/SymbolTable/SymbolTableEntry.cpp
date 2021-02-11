//
// Created by shengdebao on 2/5/21.
//

#include "SymbolTableEntry.h"
#include "Scope.h"

const SymbolTable::TypeName &SymbolTable::SymbolTableEntry::getTypeName() const {
    return typeName;
}

void SymbolTable::SymbolTableEntry::setTypeName(const SymbolTable::TypeName &typeName) {
    SymbolTableEntry::typeName = typeName;
}



SymbolTable::Scope *SymbolTable::SymbolTableEntry::getScope() const {
    return scope;
}

void SymbolTable::SymbolTableEntry::setScope(SymbolTable::Scope *scope) {
    SymbolTableEntry::scope = scope;
}

SymbolTable::SymbolTableEntry::SymbolTableEntry(const std::string &id, const SymbolTable::TypeName &typeName,
                                                SymbolTable::Scope *scope) : id(id), typeName(typeName), scope(scope) {}

std::string SymbolTable::SymbolTableEntry::getUniqueId() {
    return getScope()->getPrefix() + "_" + id;
}

