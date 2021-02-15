//
// Created by shengdebao on 2/5/21.
//

#include <cassert>
#include <iostream>
#include "Scope.h"

std::vector<SymbolTable::Scope *>SymbolTable::Scope::definedScopes;

std::string SymbolTable::Scope::getName() {return name;}

SymbolTable::Scope * SymbolTable::Scope::getPar() {return par;}

SymbolTable::SymbolTableEntry *
SymbolTable::Scope::getFunction(const std::string &id, SymbolTable::Scope *currentScope) {
    if (currentScope == nullptr)
        currentScope = this;
    SymbolTableEntry *entry = getEntry(functions, id, currentScope);
    if (entry == nullptr && par != nullptr)
        entry = par->getFunction(id, currentScope);
    if (entry == nullptr) {
        std::cerr << "id:" << id << " not found" << std::endl;
        TypeName::semanticError();
    }
    return entry;
}

SymbolTable::SymbolTableEntry * SymbolTable::Scope::getVariable(const std::string &id, Scope *currentScope) {
    if (currentScope == nullptr)
        currentScope = this;
    SymbolTableEntry *entry = getEntry(variables, id, currentScope);
    if (entry == nullptr && par != nullptr)
        entry = par->getVariable(id, currentScope);
    if (entry == nullptr) {
        std::cerr << "id:" << id << " not found" << std::endl;
        TypeName::semanticError();
    }
    return entry;
}

SymbolTable::SymbolTableEntry * SymbolTable::Scope::getEntry(std::map<std::string, SymbolTableEntry *> &mp,
                                                             const std::string &id, Scope *currentScope) {
    SymbolTableEntry *entry = nullptr;
    if (mp.count(id)) {
        entry = mp[id];
        if (entry->getAccessMode() == AccessMode::PRIVATE) {
            if (!currentScope->isImmediateClassChild(this)) {
                std::cerr << "id: " << id << " illegal private access" << std::endl;
                TypeName::semanticError();
            }
        }
        if (entry->getAccessMode() == AccessMode::PROTECTED) {
            if (!currentScope->isClassChild(this)) {
                std::cerr << "id: " << id << " illegal protected access" << std::endl;
                TypeName::semanticError();
            }
        }
    }
    return entry;
}

void SymbolTable::Scope::addEntry(const std::string &id, SymbolTable::SymbolTableEntry *entry) {
    if (entry->isFunction())
        functions[id] = entry;
    else
        variables[id] = entry;
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
    for (const auto &x : variables)
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
