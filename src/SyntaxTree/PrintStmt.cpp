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
        if (cgen.typeName.getDimension() == 0)
            if (expr_cgen.typeName.getId() == "int")
                cgen.append("Output " + expr_cgen.var + '\n');
            else if (expr_cgen.typeName.getId() == "bool")
                cgen.append("OutputB " + expr_cgen.var + "\n");
            else if (expr_cgen.typeName.getId() == "double")
                cgen.append("OutputF " + expr_cgen.var + "\n");
            else if (expr_cgen.typeName.getId() == "string") {
                cgen.append("OutputS " + expr_cgen.var + "\n");
            } else
                assert(0); // type not supported
        else
            assert (0); // dimension not supported
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
