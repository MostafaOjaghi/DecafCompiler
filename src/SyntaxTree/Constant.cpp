//
// Created by shengdebao on 2/5/21.
//

#include "Constant.h"

const std::string &SyntaxTree::Constant::getConstantValue() const {
    return constantValue;
}

void SyntaxTree::Constant::setConstantValue(const std::string &constantValue) {
    Constant::constantValue = constantValue;
}

SyntaxTree::Cgen SyntaxTree::Constant::cgen() {
    Cgen cgen;
    cgen.var = UniqueGenerator::newTemp();
    if (constantType == ConstantType::INT) {
        cgen.code += "Assign " + cgen.var + " = " + constantValue + "\n";
    } else if (constantType == ConstantType::BOOL) {
        cgen.code += "Assign " + cgen.var + " = ";
        if (constantValue == "true")
            cgen.code += "1";
        else if (constantValue == "false")
            cgen.code += "0";
        else
            assert(0);
        cgen.code += "\n";
    } else {
        assert(0);
    }
    return cgen;
}

SyntaxTree::ConstantType SyntaxTree::Constant::getConstantType() const {
    return constantType;
}

void SyntaxTree::Constant::setConstantType(SyntaxTree::ConstantType constantType) {
    Constant::constantType = constantType;
}
