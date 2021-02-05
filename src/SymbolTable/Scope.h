//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_SCOPE_H
#define DECAFCOMPILER_SCOPE_H


#include <string>
#include <map>
#include "SymbolTableEntry.h"

namespace SymbolTable {
    class Scope {
    private:
        std::string name;
        Scope *par;
        std::map<std::string, SymbolTableEntry *>mp;

    public:
        std::string getName();
        Scope * getPar();
        SymbolTableEntry * getEntry(const std::string &id);
        void addEntry(const std::string &id, SymbolTableEntry *entry);
    };
}


#endif //DECAFCOMPILER_SCOPE_H
