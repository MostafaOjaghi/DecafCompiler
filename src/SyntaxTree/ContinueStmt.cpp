//
// Created by shengdebao on 2/5/21.
//

#include "ContinueStmt.h"

SyntaxTree::Cgen SyntaxTree::ContinueStmt::cgen() {
    Cgen cgen;
    std::string label = UniqueGenerator::newLabel() + "_continue";
    cgen.append("Goto " + label + "\n");
    cgen.addContinueLabel(label);
    return cgen;
}
