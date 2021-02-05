//
// Created by shengdebao on 2/5/21.
//

#include "Scope.h"

std::string SymbolTable::Scope::getName() {return name;}

SymbolTable::Scope * SymbolTable::Scope::getPar() {return par;}
