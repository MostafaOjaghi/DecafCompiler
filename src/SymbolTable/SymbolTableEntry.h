//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_SYMBOLTABLEENTRY_H
#define DECAFCOMPILER_SYMBOLTABLEENTRY_H

#include "TypeName.h"

namespace SymbolTable {
    class SymbolTableEntry {
        TypeName typeName;
    public:
        SymbolTableEntry() = default;
        SymbolTableEntry(const TypeName &typeName);

        const TypeName &getTypeName() const;

        void setTypeName(const TypeName &type);
    };
}


#endif //DECAFCOMPILER_SYMBOLTABLEENTRY_H
