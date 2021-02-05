//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

std::string SyntaxTree::PrintStmt::cgen() {
    return std::string();
}

void SyntaxTree::PrintStmt::AddExpr(Expr *expr) {
    exprs.push_back(expr);
}
