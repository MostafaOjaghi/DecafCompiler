//
// Created by mostafa on 2/5/21.
//

#ifndef DECAFCOMPILER_PRINTSTMT_H
#define DECAFCOMPILER_PRINTSTMT_H


#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {

    class PrintStmt : public Node {
    private:
        std::vector<Expr *> exprs;

    public:
        std::string cgen() override;
        void AddExpr(Expr *expr);
    };
}

#endif //DECAFCOMPILER_PRINTSTMT_H
