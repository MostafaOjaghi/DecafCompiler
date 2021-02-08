//
// Created by shengdebao on 2/5/21.
//

#include "IfStmt.h"
#include "StmtBlock.h"

SyntaxTree::Expr *SyntaxTree::IfStmt::getConditionalExpr() const {
    return conditionalExpr;
}

void SyntaxTree::IfStmt::setConditionalExpr(SyntaxTree::Expr *conditionalExpr) {
    IfStmt::conditionalExpr = conditionalExpr;
}

SyntaxTree::Stmt *SyntaxTree::IfStmt::getTrueStmt() const {
    return trueStmt;
}

void SyntaxTree::IfStmt::setTrueStmt(SyntaxTree::Stmt *trueStmt) {
    IfStmt::trueStmt = trueStmt;
}

SyntaxTree::Stmt *SyntaxTree::IfStmt::getFalseStmt() const {
    return falseStmt;
}

void SyntaxTree::IfStmt::setFalseStmt(SyntaxTree::Stmt *falseStmt) {
    IfStmt::falseStmt = falseStmt;
}

SyntaxTree::Cgen SyntaxTree::IfStmt::cgen() {
    Cgen cgen;
    Cgen condition = conditionalExpr->cgen();
    Cgen trueCgen = trueStmt->cgen();
    Cgen falseCgen;
    std::string labelPrefix = UniqueGenerator::newLabel();
    std::string falseLabel = labelPrefix + "_false";
    std::string afterIf = labelPrefix + "_afterIf";
    if (falseStmt != nullptr)
        falseCgen = falseStmt->cgen();
    cgen.code += condition.code;
    cgen.code += "IfZ " + condition.var + " goto " + falseLabel + "\n";
    cgen.code += trueCgen.code;
    cgen.code += "Goto " + afterIf + "\n";
    cgen.code += "Label " + falseLabel + ":\n";
    cgen.code += falseCgen.code;
    cgen.code += "Label " + afterIf + ":\n";
    return cgen;
}

void SyntaxTree::IfStmt::handleScope() {
    conditionalExpr->setScope(getScope());
    conditionalExpr->handleScope();
    auto *trueScope = new SymbolTable::Scope("true", getScope());
    trueStmt->setScope(trueScope);
    trueStmt->handleScope();
    if (falseStmt != nullptr) {
        auto *falseScope = new SymbolTable::Scope("false", getScope());
        falseStmt->setScope(falseScope);
        falseStmt->handleScope();
    }
}
