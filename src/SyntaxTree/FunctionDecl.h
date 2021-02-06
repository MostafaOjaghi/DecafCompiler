//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FUNCTIONDECL_H
#define DECAFCOMPILER_FUNCTIONDECL_H


#include "Node.h"
#include "Formals.h"
#include "StmtBlock.h"

namespace SyntaxTree {

    class FunctionDecl : public Node {
    private:
        std::string functionIdentifier;
        Formals * formals;
        StmtBlock * stmtBlock;
    public:
        void handleScope() override;

        const std::string &getFunctionIdentifier() const;

        void setFunctionIdentifier(const std::string &functionIdentifier);

        Formals *getFormals() const;

        void setFormals(Formals *formals);

        StmtBlock *getStmtBlock() const;

        void setStmtBlock(StmtBlock *stmtBlock);
    };

    class FunctionDeclToTypeIdent : public FunctionDecl {

    };

    class FunctionDeclToVoidIdent : public FunctionDecl {
    };
}

#endif //DECAFCOMPILER_FUNCTIONDECL_H
