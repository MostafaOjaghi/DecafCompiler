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
        Scope *par = nullptr;
        std::map<std::string, SymbolTableEntry *>mp;

    public:
        Scope() = default;
        Scope(const std::string &name, Scope *par);

        Scope(const std::string &name);

        void setPar(Scope *par);
        std::string getName();
        std::string getPrefix();
        Scope * getPar();
        SymbolTableEntry * getEntry(const std::string &id);
        void addEntry(const std::string &id, SymbolTableEntry *entry);
    };
}


#endif //DECAFCOMPILER_SCOPE_H
