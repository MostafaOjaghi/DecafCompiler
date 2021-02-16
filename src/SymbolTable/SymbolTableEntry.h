//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_SYMBOLTABLEENTRY_H
#define DECAFCOMPILER_SYMBOLTABLEENTRY_H

#include "TypeName.h"

namespace SymbolTable {
    class Scope;

    enum class AccessMode {
        PRIVATE,
        PROTECTED,
        PUBLIC,
        NOT_FIELD
    };

    class SymbolTableEntry {
        std::string id;
        TypeName typeName;
        Scope *scope;
        AccessMode accessMode;

        bool isFunc;
        std::vector<TypeName> formals;
    public:
        AccessMode getAccessMode() const;

        void setAccessMode(AccessMode accessMode);

//        SymbolTableEntry() = default;
        SymbolTableEntry(const std::string &id, const TypeName &typeName, Scope *scope, bool isFunction = false);

        Scope *getScope() const;

        void setScope(Scope *scope);

        std::string getUniqueId();

        TypeName &getTypeName();

        void setTypeName(const TypeName &type);

        bool isFunction() const;

        void setIsFunction(bool isFunction);

        const std::vector<TypeName> &getFormals() const;

        void addFormal(const TypeName &formal);

        bool isField();
    };
}


#endif //DECAFCOMPILER_SYMBOLTABLEENTRY_H
