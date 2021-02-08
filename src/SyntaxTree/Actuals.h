//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_ACTUALS_H
#define DECAFCOMPILER_ACTUALS_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {
    class Actuals : public Node {
    private:
        std::vector<Expr *> expressions;
    public:
        const std::vector<Expr *> &getExpressions() const;
        void addExpression(Expr *expr);

        void handleScope() override;
    };
}


#endif //DECAFCOMPILER_ACTUALS_H
