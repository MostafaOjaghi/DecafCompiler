//
// Created by shengdebao on 2/5/21.
//

#include "BreakStmt.h"

SyntaxTree::Cgen SyntaxTree::BreakStmt::cgen() {
    Cgen cgen;
    std::string label = UniqueGenerator::newLabel() + "_break";
    cgen.append("Goto " + label + "\n");
    cgen.addBreakLabel(label);
    return cgen;
}

