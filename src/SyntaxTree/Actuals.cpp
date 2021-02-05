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
