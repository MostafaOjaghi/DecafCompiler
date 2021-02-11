//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_STMTS_H
#define DECAFCOMPILER_STMTS_H

#include "Node.h"
#include "Stmt.h"

namespace SyntaxTree {
    class Stmts : public Node {
    private:
        std::vector<Stmt *>stmts;
    public:
        const std::vector<Stmt *> &getStmts() const;
        void addStmt(Stmt * stmt);
        void reverseStmts();
        void handleScope() override;

        Cgen cgen() override;
    };
}


#endif //DECAFCOMPILER_STMTS_H
