//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_DECL_H
#define DECAFCOMPILER_DECL_H


#include "Node.h"
#include "VariableDecl.h"
#include "FunctionDecl.h"

namespace SyntaxTree {
    class Decl : public Node {
    };

    class DeclToVariableDecl : public Decl {
    private:
        VariableDecl *variableDecl;
    public:
        Cgen cgen() override;

        VariableDecl *getVariableDecl() const;

        void setVariableDecl(VariableDecl *variableDecl);
    };

    class DeclToFunctionDecl : public Decl {
    private:
        FunctionDecl *functionDecl;
    public:
        Cgen cgen() override;

        FunctionDecl *getFunctionDecl() const;

        void setFunctionDecl(FunctionDecl *functionDecl);

    };

    class DeclToInterfaceDecl : public Decl {
    };
}

#endif //DECAFCOMPILER_DECL_H
