//
// Created by shengdebao on 2/5/21.
//

#include "ForStmt.h"
#include "Stmt.h"

SyntaxTree::Expr *SyntaxTree::ForStmt::getForInit() const {
    return forInit;
}

void SyntaxTree::ForStmt::setForInit(SyntaxTree::Expr *forInit) {
    ForStmt::forInit = forInit;
}

SyntaxTree::Expr *SyntaxTree::ForStmt::getForCondition() const {
    return forCondition;
}

void SyntaxTree::ForStmt::setForCondition(SyntaxTree::Expr *forCondition) {
    ForStmt::forCondition = forCondition;
}

SyntaxTree::Expr *SyntaxTree::ForStmt::getForStep() const {
    return forStep;
}

void SyntaxTree::ForStmt::setForStep(SyntaxTree::Expr *forStep) {
    ForStmt::forStep = forStep;
}

SyntaxTree::Stmt *SyntaxTree::ForStmt::getStmt() const {
    return stmt;
}

void SyntaxTree::ForStmt::setStmt(SyntaxTree::Stmt *stmt) {
    ForStmt::stmt = stmt;
}

SyntaxTree::Cgen SyntaxTree::ForStmt::cgen() {
    Cgen cgen;
    Cgen condition = forCondition->cgen();
    Cgen body = stmt->cgen();
    std::string labelPrefix = UniqueGenerator::newLabel();
    std::string startLabel = labelPrefix + "_startFor";
    std::string stepLabel = labelPrefix + "_stepFor";
    std::string endLabel = labelPrefix + "_endFor";
    if (forInit != nullptr) {
        Cgen init = forInit->cgen();
        cgen.code += init.code;
    }
    cgen.code += "Label " + startLabel + ":\n";
    cgen.code += condition.code;
    cgen.code += "IfZ " + condition.var + " Goto " + endLabel + "\n";
    cgen.code += body.code;
    cgen.code += "Label " + stepLabel + ":\n";
    if (forStep != nullptr) {
        Cgen step = forStep->cgen();
        cgen.code += step.code;
    }
    cgen.code += "Goto " + startLabel + "\n";
    cgen.code += "Label " + endLabel + ":\n";
    return cgen;
}

void SyntaxTree::ForStmt::handleScope() {
    if (forInit != nullptr) {
        forInit->setScope(getScope());
        forInit->handleScope();
    }
    forCondition->setScope(getScope());
    forCondition->handleScope();
    if (forStep != nullptr) {
        forStep->setScope(getScope());
        forStep->handleScope();
    }
    auto *scope = new SymbolTable::Scope("forBody",getScope());
    stmt->setScope(scope);
    stmt->handleScope();
}
