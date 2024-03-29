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
    if (forInit != nullptr)
        cgen.append(forInit->cgen());
    cgen.append("Label " + startLabel + ":\n");
    cgen.append(condition);
    cgen.append("IfZ " + condition.var + " Goto " + endLabel + "\n");
    cgen.append(body);
    cgen.append("Label " + stepLabel + ":\n");
    cgen.append(cgen.getContinueLabels());
    if (forStep != nullptr)
        cgen.append(forStep->cgen());
    cgen.append("Goto " + startLabel + "\n");
    cgen.append("Label " + endLabel + ":\n");
    cgen.append(cgen.getBreakLabels());
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

void SyntaxTree::ForStmt::handleClassHierarchy() {
    if (this->getForCondition() != nullptr)
        this->getForCondition()->handleClassHierarchy();
    if (this->getForInit() != nullptr)
        this->getForInit()->handleClassHierarchy();
    if (this->getForStep() != nullptr)
        this->getForStep()->handleClassHierarchy();
    if (this->getStmt() != nullptr) {
        this->getStmt()->handleClassHierarchy();
    }
}
