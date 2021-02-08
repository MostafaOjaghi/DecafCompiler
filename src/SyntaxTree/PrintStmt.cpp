//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

SyntaxTree::Cgen SyntaxTree::PrintStmt::cgen() {
    Cgen cgen;
    // TODO handle other types
    for (Expr *actual : actuals->getExpressions()) {
        Cgen expr_cgen = actual->cgen();
        cgen.code += expr_cgen.code;
        cgen.code += "Output " + expr_cgen.var + '\n';
    }
    return cgen;
}

SyntaxTree::Actuals *SyntaxTree::PrintStmt::getActuals() const {
    return actuals;
}

void SyntaxTree::PrintStmt::setActuals(SyntaxTree::Actuals *actuals) {
    PrintStmt::actuals = actuals;
}

void SyntaxTree::PrintStmt::handleScope() {
    actuals->setScope(getScope());
    actuals->handleScope();
}
