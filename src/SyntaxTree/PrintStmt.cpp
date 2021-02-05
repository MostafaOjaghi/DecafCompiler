//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

std::string SyntaxTree::PrintStmt::cgen() {
    return std::string();
}

SyntaxTree::Actuals *SyntaxTree::PrintStmt::getActuals() const {
    return actuals;
}

void SyntaxTree::PrintStmt::setActuals(SyntaxTree::Actuals *actuals) {
    PrintStmt::actuals = actuals;
}
