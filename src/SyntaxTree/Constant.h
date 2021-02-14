//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_CONSTANT_H
#define DECAFCOMPILER_CONSTANT_H

#include "Node.h"

namespace SyntaxTree {
    enum class ConstantType {
        INT,
        BOOL,
        DOUBLE,
        STRING,
        NULL_POINTER
    };

    class Constant : public Node {
    private:
        ConstantType constantType;
        std::string constantValue;
    public:
        Cgen cgen() override;

        ConstantType getConstantType() const;

        void setConstantType(ConstantType constantType);

        const std::string &getConstantValue() const;

        void setConstantValue(const std::string &constantValue);
        std::string getConstantTypeString();
    };
}


#endif //DECAFCOMPILER_CONSTANT_H
