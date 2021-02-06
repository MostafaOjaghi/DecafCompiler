//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

SyntaxTree::Cgen SyntaxTree::PrintStmt::cgen() {
    Cgen cgen;
    // TODO complete
    return cgen;
}

SyntaxTree::Actuals *SyntaxTree::PrintStmt::getActuals() const {
    return actuals;
}

void SyntaxTree::PrintStmt::setActuals(SyntaxTree::Actuals *actuals) {
    PrintStmt::actuals = actuals;
}
