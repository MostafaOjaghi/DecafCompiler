//
// Created by mostafa on 2/5/21.
//

#include "PrintStmt.h"

SyntaxTree::Cgen SyntaxTree::PrintStmt::cgen() {
    Cgen cgen;
    for (Expr *expr : exprs) {
        Cgen expr_cgen = expr->cgen();
        cgen.code += expr_cgen.code;
        cgen.code += "Output " + expr_cgen.var + "\n";
    }
    return cgen;
}

void SyntaxTree::PrintStmt::addExpr(Expr *expr) {
    exprs.push_back(expr);
}
