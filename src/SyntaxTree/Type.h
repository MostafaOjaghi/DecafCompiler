//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_TYPE_H
#define DECAFCOMPILER_TYPE_H

#include "Node.h"

namespace SyntaxTree {
    class Type : public Node {
        std::string typeNameID;
        int dimension;
    public:
        Cgen cgen() override;

        int getDimension() const;

        void setDimension(int dimension);

        void incrementDimension();

        const std::string &getTypeNameId() const;

        void setTypeNameId(const std::string &typeNameId);
    };

    class TypeToInt : public Type{

    };

    class TypeToDouble : public Type {

    };

    class TypeToBool : public Type {};

    class TypeToString : public Type {};

    class TypeToIdent : public Type {};

    class TypeToTypeArray : public Type {};

}


#endif //DECAFCOMPILER_TYPE_H
