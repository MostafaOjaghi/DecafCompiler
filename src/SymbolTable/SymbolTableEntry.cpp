//
// Created by shengdebao on 2/5/21.
//

#include "SymbolTableEntry.h"
#include "Scope.h"

SymbolTable::TypeName &SymbolTable::SymbolTableEntry::getTypeName() {
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
                                                SymbolTable::Scope *scope, bool isFunction) :
        id(id),
        typeName(typeName),
        scope(scope),
        isFunc(isFunction) {
    this->accessMode = SymbolTable::AccessMode::PUBLIC;
}

std::string SymbolTable::SymbolTableEntry::getUniqueId() {
    if (isFunction())
        return "func_" + getScope()->getPrefix() + "_" + id;
    else
        return getScope()->getPrefix() + "_" + id;
}

SymbolTable::AccessMode SymbolTable::SymbolTableEntry::getAccessMode() const {
    return accessMode;
}

void SymbolTable::SymbolTableEntry::setAccessMode(SymbolTable::AccessMode accessMode) {
    SymbolTableEntry::accessMode = accessMode;
}

bool SymbolTable::SymbolTableEntry::isFunction() const {
    return isFunc;
}

void SymbolTable::SymbolTableEntry::setIsFunction(bool isFunction) {
    SymbolTableEntry::isFunc = isFunction;
}

const std::vector<SymbolTable::TypeName> &SymbolTable::SymbolTableEntry::getFormals() const {
    return formals;
}

void SymbolTable::SymbolTableEntry::addFormal(const SymbolTable::TypeName &formal) {
    formals.push_back(formal);
}

