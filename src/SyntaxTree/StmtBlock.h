//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_STMTBLOCK_H
#define DECAFCOMPILER_STMTBLOCK_H

#include "Node.h"
#include "Stmts.h"
#include "VariableDecls.h"

namespace SyntaxTree {
    class StmtBlock : public Node {
    private:
        Stmts * stmts;
        VariableDecls * variableDecls;
    public:
        void handleScope() override;

        Stmts *getStmts() const;

        void setStmts(Stmts *stmts);

        VariableDecls *getVariableDecls() const;

        void setVariableDecls(VariableDecls *variableDecls);

        Cgen cgen() override;
    };
}


#endif //DECAFCOMPILER_STMTBLOCK_H
