//
// Created by shengdebao on 2/5/21.
//

#include "Scope.h"

std::string SymbolTable::Scope::getName() {return name;}

SymbolTable::Scope * SymbolTable::Scope::getPar() {return par;}

SymbolTable::SymbolTableEntry * SymbolTable::Scope::getEntry(const std::string &id) {
    if (mp.count(id))
        return mp[id];
    return nullptr;
}

void SymbolTable::Scope::addEntry(const std::string &id, SymbolTable::SymbolTableEntry *entry) {
    mp[id]=entry;
}

SymbolTable::Scope::Scope(const std::string &name, SymbolTable::Scope *par) : name(name), par(par) {
    this->par = par;
    this->name = name;
}

void SymbolTable::Scope::setPar(SymbolTable::Scope *par) {
    Scope::par = par;
}

SymbolTable::Scope::Scope(const std::string &name) : name(name) {
    this->name = name;
}
