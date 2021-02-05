//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FORSTMT_H
#define DECAFCOMPILER_FORSTMT_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {
    class Stmt;

    class ForStmt : public Node {
    private:
        Expr *forInit;
        Expr *forCondition;
        Expr *forStep;
        Stmt *stmt;
    public:
        Expr *getForInit() const;

        void setForInit(Expr *forInit);

        Expr *getForCondition() const;

        void setForCondition(Expr *forCondition);

        Expr *getForStep() const;

        void setForStep(Expr *forStep);

        Stmt *getStmt() const;

        void setStmt(Stmt *stmt);
    };
}


#endif //DECAFCOMPILER_FORSTMT_H
