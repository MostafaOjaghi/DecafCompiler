//
// Created by shengdebao on 2/5/21.
//

#include "WhileStmt.h"
#include "Stmt.h"

SyntaxTree::Expr *SyntaxTree::WhileStmt::getConditionalExpr() const {
    return conditionalExpr;
}

void SyntaxTree::WhileStmt::setConditionalExpr(SyntaxTree::Expr *conditionalExpr) {
    WhileStmt::conditionalExpr = conditionalExpr;
}

SyntaxTree::Stmt *SyntaxTree::WhileStmt::getStmt() const {
    return stmt;
}

void SyntaxTree::WhileStmt::setStmt(SyntaxTree::Stmt *stmt) {
    WhileStmt::stmt = stmt;
}

SyntaxTree::Cgen SyntaxTree::WhileStmt::cgen() {
    Cgen cgen;
    Cgen condition = conditionalExpr->cgen();
    Cgen body = stmt->cgen();
    std::string labelPrefix = UniqueGenerator::newLabel();
    std::string startLabel = labelPrefix + "_startWhile";
    std::string endLabel = labelPrefix + "_endWhile";
    cgen.append("Label " + startLabel + ":\n");
    cgen.append(condition);
    cgen.append("IfZ " + condition.var + " Goto " + endLabel + "\n");
    cgen.append(body);
    cgen.append("Goto " + startLabel + "\n");
    cgen.append("Label " + endLabel + ":\n");
    return cgen;
}

void SyntaxTree::WhileStmt::handleScope() {
    conditionalExpr->setScope(getScope());
    conditionalExpr->handleScope();
    auto *scope = new SymbolTable::Scope("whileBody",getScope());
    stmt->setScope(scope);
    stmt->handleScope();
}
