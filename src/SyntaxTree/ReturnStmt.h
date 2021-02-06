//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_RETURNSTMT_H
#define DECAFCOMPILER_RETURNSTMT_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {

    class ReturnStmt : public Node {
    private:
        Expr *expr;
    public:
        void handleScope() override;

        Expr *getExpr() const;

        void setExpr(Expr *expr);
    };
    class returnStmtToReturnExpr : public ReturnStmt {

    };
}


#endif //DECAFCOMPILER_RETURNSTMT_H
