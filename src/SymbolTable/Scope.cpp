//
// Created by shengdebao on 2/5/21.
//

#include <cassert>
#include <iostream>
#include "Scope.h"

std::vector<SymbolTable::Scope *>SymbolTable::Scope::definedScopes;

std::string SymbolTable::Scope::getName() {return name;}

SymbolTable::Scope * SymbolTable::Scope::getPar() {return par;}

SymbolTable::SymbolTableEntry * SymbolTable::Scope::getEntry(const std::string &id, Scope *currentScope) {
    if (currentScope == nullptr)
        currentScope = this;

    SymbolTableEntry *entry = nullptr;
    if (mp.count(id)) {
        entry = mp[id];
        if (entry->getAccessMode() == AccessMode::PRIVATE) {
            if (!currentScope->isImmediateClassChild(this)) {
                std::cerr << "id: " << id << " illegal private access" << std::endl;
                assert(0);
            }
        }
        if (entry->getAccessMode() == AccessMode::PROTECTED) {
            if (!currentScope->isClassChild(this)) {
                std::cerr << "id: " << id << " illegal protected access" << std::endl;
                assert(0);
            }
        }
        return entry;
    }
    if (par != nullptr)
        entry = par->getEntry(id, currentScope);
    if (entry == nullptr) {
        std::cerr << "id:" << id << " not found" << std::endl;
        assert(0);
    }
    return entry;
}

void SymbolTable::Scope::addEntry(const std::string &id, SymbolTable::SymbolTableEntry *entry) {
    mp[id]=entry;
}

SymbolTable::Scope::Scope(const std::string &name, SymbolTable::Scope *par) : name(name), par(par) {
    this->par = par;
    this->name = name;
    definedScopes.push_back(this);
}

void SymbolTable::Scope::setPar(SymbolTable::Scope *par) {
    Scope::par = par;
}

SymbolTable::Scope::Scope(const std::string &name) : name(name) {
    this->name = name;
    definedScopes.push_back(this);
}

std::string SymbolTable::Scope::getPrefix() {
    if (par == nullptr)
        return getName();
    if (getName().empty())
        return par->getPrefix();
    return par->getPrefix() + "_" + getName();
}

const std::vector<SymbolTable::Scope *> &SymbolTable::Scope::getDefinedScopes() {
    return definedScopes;
}

std::vector<SymbolTable::SymbolTableEntry *> SymbolTable::Scope::getEntries() {
    std::vector<SymbolTableEntry *>ret;
    for (const auto &x : mp)
        ret.push_back(x.second);
    return ret;
}

bool SymbolTable::Scope::isImmediateClassChild(SymbolTable::Scope *classScope) {
    auto cur = this;
    while (cur != nullptr && !cur->isClass() && classScope != cur) {
        cur = cur->getPar();
    }
    return cur == classScope;
}

bool SymbolTable::Scope::isClassChild(SymbolTable::Scope *classScope) {
    auto cur = this;
    while (cur != nullptr && cur->getPar() != nullptr && classScope != cur) {
        cur = cur->getPar();
    }
    return cur == classScope;
}

bool SymbolTable::Scope::isClass() const {
    return isClss;
}

void SymbolTable::Scope::setIsClass(bool isClass) {
    Scope::isClss = isClass;
}
