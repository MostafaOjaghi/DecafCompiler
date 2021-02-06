//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_VARIABLE_H
#define DECAFCOMPILER_VARIABLE_H

#include "Node.h"
#include "Type.h"

namespace SyntaxTree {
    class Variable : public Node {
        Type *type;
    public:
        Type *getType() const;

        void setType(Type *type);

        const std::string &getId() const;

        void setId(const std::string &id);

    private:
        std::string id;
    public:
        Cgen cgen() override;
    };
}

#endif //DECAFCOMPILER_VARIABLE_H
