//
// Created by shengdebao on 2/5/21.
//

#include "Stmt.h"
#include "StmtBlock.h"

SyntaxTree::PrintStmt *SyntaxTree::StmtToPrintStmt::getPrintStmt() const {
    return printStmt;
}

void SyntaxTree::StmtToPrintStmt::setPrintStmt(SyntaxTree::PrintStmt *printStmt) {
    StmtToPrintStmt::printStmt = printStmt;
}

SyntaxTree::Cgen SyntaxTree::StmtToPrintStmt::cgen() {
    return printStmt->cgen();
}

void SyntaxTree::StmtToPrintStmt::handleScope() {
    this->getPrintStmt()->setScope(this->getScope());
    this->getPrintStmt()->handleScope();
}

SyntaxTree::Expr *SyntaxTree::StmtToExpr::getExpr() const {
    return expr;
}

void SyntaxTree::StmtToExpr::setExpr(SyntaxTree::Expr *expr) {
    StmtToExpr::expr = expr;
}

SyntaxTree::Cgen SyntaxTree::StmtToExpr::cgen() {
    return expr->cgen();
}

void SyntaxTree::StmtToExpr::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
}

SyntaxTree::IfStmt *SyntaxTree::StmtToIfStmt::getIfStmt() const {
    return ifStmt;
}

void SyntaxTree::StmtToIfStmt::setIfStmt(SyntaxTree::IfStmt *ifStmt) {
    StmtToIfStmt::ifStmt = ifStmt;
}

SyntaxTree::Cgen SyntaxTree::StmtToIfStmt::cgen() {
    return ifStmt->cgen();
}

void SyntaxTree::StmtToIfStmt::handleScope() {
    ifStmt->setScope(getScope());
    getIfStmt()->handleScope();
}

SyntaxTree::WhileStmt *SyntaxTree::StmtToWhileStmt::getWhileStmt() const {
    return whileStmt;
}

void SyntaxTree::StmtToWhileStmt::setWhileStmt(SyntaxTree::WhileStmt *whileStmt) {
    StmtToWhileStmt::whileStmt = whileStmt;
}

SyntaxTree::Cgen SyntaxTree::StmtToWhileStmt::cgen() {
    return whileStmt->cgen();
}

void SyntaxTree::StmtToWhileStmt::handleScope() {
    whileStmt->setScope(getScope());
    whileStmt->handleScope();
}

SyntaxTree::ForStmt *SyntaxTree::StmtToForStmt::getForStmt() const {
    return forStmt;
}

void SyntaxTree::StmtToForStmt::setForStmt(SyntaxTree::ForStmt *forStmt) {
    StmtToForStmt::forStmt = forStmt;
}

SyntaxTree::BreakStmt *SyntaxTree::StmtToBreakStmt::getBreakStmt() const {
    return breakStmt;
}

void SyntaxTree::StmtToBreakStmt::setBreakStmt(SyntaxTree::BreakStmt *breakStmt) {
    StmtToBreakStmt::breakStmt = breakStmt;
}

SyntaxTree::ContinueStmt *SyntaxTree::StmtToContinueStmt::getContinueStmt() const {
    return continueStmt;
}

void SyntaxTree::StmtToContinueStmt::setContinueStmt(SyntaxTree::ContinueStmt *continueStmt) {
    StmtToContinueStmt::continueStmt = continueStmt;
}

SyntaxTree::ReturnStmt *SyntaxTree::StmtToReturnStmt::getReturnStmt() const {
    return returnStmt;
}

void SyntaxTree::StmtToReturnStmt::setReturnStmt(SyntaxTree::ReturnStmt *returnStmt) {
    StmtToReturnStmt::returnStmt = returnStmt;
}

SyntaxTree::StmtBlock *SyntaxTree::StmtToStmtBlock::getStmtBlock() const {
    return stmtBlock;
}

void SyntaxTree::StmtToStmtBlock::setStmtBlock(SyntaxTree::StmtBlock *stmtBlock) {
    StmtToStmtBlock::stmtBlock = stmtBlock;
}

void SyntaxTree::StmtToStmtBlock::handleScope() {
    auto *scope = new SymbolTable::Scope("block", getScope());
    this->getStmtBlock()->setScope(scope);
    this->getStmtBlock()->handleScope();
}

SyntaxTree::Cgen SyntaxTree::StmtToStmtBlock::cgen() {
    return stmtBlock->cgen();
}
