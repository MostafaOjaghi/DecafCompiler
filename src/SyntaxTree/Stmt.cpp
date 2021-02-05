//
// Created by shengdebao on 2/5/21.
//

#include "Stmt.h"

SyntaxTree::PrintStmt *SyntaxTree::StmtToPrintStmt::getPrintStmt() const {
    return printStmt;
}

void SyntaxTree::StmtToPrintStmt::setPrintStmt(SyntaxTree::PrintStmt *printStmt) {
    StmtToPrintStmt::printStmt = printStmt;
}
