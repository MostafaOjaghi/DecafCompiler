//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

SyntaxTree::Cgen SyntaxTree::PrintStmt::cgen() {
    Cgen cgen;
    // TODO handle other types
    for (Expr *actual : actuals->getExpressions()) {
        Cgen expr_cgen = actual->cgen();
        cgen.append(expr_cgen);
        cgen.append("Output " + expr_cgen.var + '\n');
    }
    cgen.append("Endl\n");
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
