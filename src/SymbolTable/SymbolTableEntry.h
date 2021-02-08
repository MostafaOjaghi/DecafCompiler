//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_SYMBOLTABLEENTRY_H
#define DECAFCOMPILER_SYMBOLTABLEENTRY_H

#include "TypeName.h"

namespace SymbolTable {
    class Scope;

    class SymbolTableEntry {
        std::string id;
        TypeName typeName;
        Scope *scope;
    public:
//        SymbolTableEntry() = default;
        SymbolTableEntry(const std::string &id, const TypeName &typeName, Scope *scope);

        Scope *getScope() const;

        void setScope(Scope *scope);

        std::string getUniqueId();

        const TypeName &getTypeName() const;

        void setTypeName(const TypeName &type);
    };
}


#endif //DECAFCOMPILER_SYMBOLTABLEENTRY_H
