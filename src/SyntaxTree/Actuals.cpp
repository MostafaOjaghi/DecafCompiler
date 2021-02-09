//
// Created by shengdebao on 2/5/21.
//

#include "Actuals.h"

const std::vector<SyntaxTree::Expr *> &SyntaxTree::Actuals::getExpressions() const {
    return expressions;
}

void SyntaxTree::Actuals::addExpression(SyntaxTree::Expr *expr) {
    expressions.push_back(expr);
}

void SyntaxTree::Actuals::handleScope() {
    for (Expr *expr : expressions) {
        expr->setScope(getScope());
        expr->handleScope();
    }
}

SyntaxTree::Cgen SyntaxTree::Actuals::cgen() {
    Cgen cgen;
    for (Expr *expr : expressions) {
        Cgen expr_cgen = expr->cgen();
        cgen.append(expr_cgen);
        cgen.append("Pushparam " + expr_cgen.var + "\n");
    }
    return cgen;
}
