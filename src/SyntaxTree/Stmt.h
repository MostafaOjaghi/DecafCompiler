//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_STMT_H
#define DECAFCOMPILER_STMT_H

#include "Node.h"

namespace SyntaxTree {
    class Stmt : public Node {

    };

    class StmtToExpr : public Stmt {

    };

    class StmtToIfStmt : public Stmt {

    };

    class StmtToWhileStmt : public Stmt {

    };

    class StmtToForStmt : public Stmt {

    };

    class StmtToBreakStmt : public Stmt {

    };

    class StmtToContinueStmt : public Stmt {

    };

    class StmtToReturnStmt : public Stmt {

    };

    class StmtToPrintStmt : public Stmt {

    };

    class StmtToStmtBlock : public Stmt {

    };
}


#endif //DECAFCOMPILER_STMT_H
