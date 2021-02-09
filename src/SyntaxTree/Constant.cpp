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
    cgen.createVar();
    if (constantType == ConstantType::INT) {
        cgen.append("Assign " + cgen.var + " = " + constantValue + "\n");
    } else if (constantType == ConstantType::BOOL) {
        std::string code = "Assign " + cgen.var + " = ";
        if (constantValue == "true")
            code += "1";
        else if (constantValue == "false")
            code += "0";
        else
            assert(0);
        code += "\n";
        cgen.append(code);
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
