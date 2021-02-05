//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_IFSTMT_H
#define DECAFCOMPILER_IFSTMT_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {
    class Stmt;

    class IfStmt : public Node {
    private:
        Expr *conditionalExpr;
        Stmt *trueStmt;
        Stmt *falseStmt;
    public:
        Expr *getConditionalExpr() const;

        void setConditionalExpr(Expr *conditionalExpr);

        Stmt *getTrueStmt() const;

        void setTrueStmt(Stmt *trueStmt);

        Stmt *getFalseStmt() const;

        void setFalseStmt(Stmt *falseStmt);
    };

}


#endif //DECAFCOMPILER_IFSTMT_H
