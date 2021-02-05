//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_WHILESTMT_H
#define DECAFCOMPILER_WHILESTMT_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {
    class Stmt;

    class WhileStmt : public Node {
    private:
        Expr *conditionalExpr;
        Stmt *stmt;
    public:
        Stmt *getStmt() const;

        void setStmt(Stmt *stmt);

        Expr *getConditionalExpr() const;

        void setConditionalExpr(Expr *conditionalExpr);
    };
}


#endif //DECAFCOMPILER_WHILESTMT_H
