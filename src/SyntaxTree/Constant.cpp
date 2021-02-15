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
    if (constantType == ConstantType::INT) {
        cgen.createVar("int", 0);
        cgen.append("Assign " + cgen.var + " = " + constantValue + "\n");
    } else if (constantType == ConstantType::BOOL) {
        cgen.createVar("bool", 0);
        std::string code = "Assign " + cgen.var + " = ";
        if (constantValue == "true")
            code += "1";
        else if (constantValue == "false")
            code += "0";
        else
            assert(0);
        code += "\n";
        cgen.append(code);
    } else if (constantType == ConstantType::DOUBLE) {
        cgen.createVar("double", 0);
        cgen.append("AssignF " + cgen.var + " = " + constantValue + "\n");
    } else if (constantType == ConstantType::STRING) {
        cgen.createVar("string", 0);
        cgen.append("AssignS " + cgen.var + " = " + constantValue + "\n");
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

std::string SyntaxTree::Constant::getConstantTypeString(){
    if (constantType == ConstantType::BOOL) {
        return "bool";
    } else if (constantType == ConstantType::DOUBLE) {
        return "double";
    } else if (constantType == ConstantType::INT) {
        return "int";
    } else if (constantType == ConstantType::STRING) {
        return "string";
    } else if (constantType == ConstantType::NULL_POINTER) {
        return "nullptr";
    } else {
        return "undefined";
    }
}
