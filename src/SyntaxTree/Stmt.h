//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_STMT_H
#define DECAFCOMPILER_STMT_H

#include "Node.h"
#include "PrintStmt.h"
#include "IfStmt.h"
#include "WhileStmt.h"
#include "ForStmt.h"
#include "BreakStmt.h"
#include "ContinueStmt.h"
#include "ReturnStmt.h"

namespace SyntaxTree {
    class StmtBlock;

    class Stmt : public Node {

    };

    class StmtToExpr : public Stmt {
    private:
        Expr *expr;
    public:
        Expr *getExpr() const;

        void setExpr(Expr *expr);
    };

    class StmtToIfStmt : public Stmt {
    private:
        IfStmt *ifStmt;
    public:
        IfStmt *getIfStmt() const;

        void setIfStmt(IfStmt *ifStmt);
    };

    class StmtToWhileStmt : public Stmt {
    private:
        WhileStmt *whileStmt;
    public:
        WhileStmt *getWhileStmt() const;

        void setWhileStmt(WhileStmt *whileStmt);
    };

    class StmtToForStmt : public Stmt {
    private:
        ForStmt *forStmt;
    public:
        ForStmt *getForStmt() const;

        void setForStmt(ForStmt *forStmt);
    };

    class StmtToBreakStmt : public Stmt {
    private:
        BreakStmt *breakStmt;
    public:
        BreakStmt *getBreakStmt() const;

        void setBreakStmt(BreakStmt *breakStmt);
    };

    class StmtToContinueStmt : public Stmt {
    private:
        ContinueStmt *continueStmt;
    public:
        ContinueStmt *getContinueStmt() const;

        void setContinueStmt(ContinueStmt *continueStmt);
    };

    class StmtToReturnStmt : public Stmt {
    private:
        ReturnStmt *returnStmt;
    public:
        ReturnStmt *getReturnStmt() const;

        void setReturnStmt(ReturnStmt *returnStmt);
    };

    class StmtToPrintStmt : public Stmt {
        PrintStmt * printStmt;
    public:
        PrintStmt *getPrintStmt() const;

        void setPrintStmt(PrintStmt *printStmt);

        Cgen cgen() override;
    };

    class StmtToStmtBlock : public Stmt {
    private:
        StmtBlock *stmtBlock;
    public:
        StmtBlock *getStmtBlock() const;

        void setStmtBlock(StmtBlock *stmtBlock);
    };
}


#endif //DECAFCOMPILER_STMT_H
