//
// Created by mostafa on 2/5/21.
//

#include <algorithm>
#include <cassert>
#include <iostream>
#include "ClassType.h"
#include "Scope.h"

std::map<std::string, SymbolTable::ClassType *>SymbolTable::ClassType::mp;

SymbolTable::ClassType *SymbolTable::ClassType::getParent() const {
    return parent;
}

const std::string &SymbolTable::ClassType::getId() const {
    return Id;
}

void SymbolTable::ClassType::setId(const std::string &id) {
    Id = id;
}

void SymbolTable::ClassType::setParent(SymbolTable::ClassType *parent) {
    ClassType::parent = parent;
}

void SymbolTable::ClassType::addType(SymbolTable::ClassType * classType) {
    mp[classType->getId()] = classType;
}

SymbolTable::ClassType *SymbolTable::ClassType::getClass(std::string className) {
    if (mp.count(className))
        return mp[className];
    return nullptr;
}

SymbolTable::ClassType::ClassType(const std::string &id) : Id(id) {
}

void SymbolTable::ClassType::handleHierarchy() {
    if (handleHierarchyCalled)
        return;
    handleHierarchyCalled = true;
    if (!this->getParentName().empty()) {
        auto classType = SymbolTable::ClassType::getClass(getParentName());
        this->getScope()->setPar(classType->getScope());
        this->parent = classType;
        this->parent->handleHierarchy();
    }
    // TODO: complete function for interface

}

const std::string &SymbolTable::ClassType::getParentName() const {
    return parentName;
}

void SymbolTable::ClassType::setParentName(const std::string &parentName) {
    ClassType::parentName = parentName;
}

SymbolTable::Scope *SymbolTable::ClassType::getScope() const {
    return scope;
}

void SymbolTable::ClassType::setScope(SymbolTable::Scope *scope) {
    ClassType::scope = scope;
}

void SymbolTable::ClassType::addToLayout(const std::string &s) {
    objectLayout.push_back(s);
}

int SymbolTable::ClassType::getIndexInObjectLayout(const std::string &s) {
    int index = std::find(objectLayout.begin(), objectLayout.end(), s) - objectLayout.begin();

    if (index == (int) objectLayout.size()) {
        if (this->getParent() == nullptr) {
            std::cerr << "Field access not valid!" << std::endl;
            assert(0);
        }
        return this->getParent()->getIndexInObjectLayout(s);
    }
    int t = this->getParent() == nullptr ? 1 : this->getParent()->getObjectLayoutSize();
    return t + index;
}

int SymbolTable::ClassType::getObjectLayoutSize() {
    if (this->getParent() != nullptr)
        return this->getParent()->getObjectLayoutSize() + (int) objectLayout.size();
    return (int) objectLayout.size() + 1;
}

void SymbolTable::ClassType::addMethod(std::string id) {
    methods.push_back(id);
}

int SymbolTable::ClassType::getMethodPosition(std::string id) {
    return 1 + getMethodIndex(id);
}

int SymbolTable::ClassType::getMethodIndex(std::string id) {
    if (parent != nullptr && parent->hasMethod(id))
        return parent->getMethodIndex(id);
    int pos = 0;
    if (parent != nullptr)
        pos = parent->getVtableSize();
    for (const std::string &method : methods) {
        if (method == id)
            break;
        if (parent == nullptr || !parent->hasMethod(method))
            pos++;
    }
    return pos;
}

int SymbolTable::ClassType::getVtableSize() {
    int vtable_size = 1;
    if (parent != nullptr)
        vtable_size = parent->getVtableSize();
    for (std::string id : methods)
        if (parent == nullptr || !parent->hasMethod(id))
            vtable_size++;
    return vtable_size;
}

bool SymbolTable::ClassType::hasMethod(std::string id) {
    bool has = std::find(methods.begin(), methods.end(), id) != methods.end();
    bool parent_has;
    if (parent != nullptr) {
        parent_has = parent->hasMethod(id);
    }
    return has || parent_has;
}

std::vector<std::string> SymbolTable::ClassType::getVtable() {
    std::vector<std::string> vtable;
    if (parent != nullptr)
        vtable = parent->getVtable();
    for (const std::string &method : methods)
        if (parent != nullptr && parent->hasMethod(method))
            vtable[parent->getMethodIndex(method)] = getScope()->getFunction(method)->getUniqueId();
        else
            vtable.push_back(getScope()->getFunction(method)->getUniqueId());
    return vtable;
}


