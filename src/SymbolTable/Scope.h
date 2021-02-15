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
        static std::vector<Scope *>definedScopes;
    public:
        static const std::vector<Scope *> &getDefinedScopes();

    private:

        std::string name;
        Scope *par = nullptr;
        std::map<std::string, SymbolTableEntry *> variables;
        std::map<std::string, SymbolTableEntry *> functions;
        bool isClss = false;

        SymbolTableEntry *getEntry(std::map<std::string, SymbolTableEntry *> &mp,
                                   const std::string &id, Scope *currentScope);

    public:
        bool isClass() const;

        void setIsClass(bool isClass);

        Scope() = default;
        Scope(const std::string &name, Scope *par);

        Scope(const std::string &name);

        void setPar(Scope *par);
        std::string getName();
        std::string getPrefix();
        Scope * getPar();
        SymbolTableEntry * getVariable(const std::string &id, Scope * currentScope = nullptr);
        SymbolTableEntry * getFunction(const std::string &id, Scope * currentScope = nullptr);
        void addEntry(const std::string &id, SymbolTableEntry *entry);
        std::vector<SymbolTableEntry *> getEntries();

        bool isImmediateClassChild(Scope *classScope);

        bool isClassChild(Scope *classScope);
    };
}


#endif //DECAFCOMPILER_SCOPE_H
