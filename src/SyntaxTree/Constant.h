//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_CONSTANT_H
#define DECAFCOMPILER_CONSTANT_H

#include "Node.h"

namespace SyntaxTree {
    class Constant : public Node {
    private:
        std::string constantIdType;
        std::string constantValue;
    public:
        const std::string &getConstantIdType() const;

        void setConstantIdType(const std::string &constantIdType);

        const std::string &getConstantValue() const;

        void setConstantValue(const std::string &constantValue);
    };
}


#endif //DECAFCOMPILER_CONSTANT_H
