//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_RESULTTYPE_H
#define DECAFCOMPILER_RESULTTYPE_H
#include <string>
#include <vector>
#include "ClassType.h"

namespace SymbolTable {
    class TypeName {
        std::string id;
        ClassType *classType = nullptr;
        int dimension = 0;
    public:
        TypeName(std::string id, int dimension);
        TypeName() = default;

        static void semanticError();

        int getDimension() const;

        void setDimension(int dimension);

        const std::string &getId() const;

        void setId(const std::string &id);

        ClassType *getClassType() const;

        void setClassType(ClassType *classType);

        bool isPrimitive() const;

        bool isArray() const;
        static bool checkCastable(TypeName from, TypeName to);
    };
}


#endif //DECAFCOMPILER_RESULTTYPE_H
