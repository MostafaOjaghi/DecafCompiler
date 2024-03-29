//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_DECL_H
#define DECAFCOMPILER_DECL_H


#include "Node.h"
#include "VariableDecl.h"
#include "FunctionDecl.h"
#include "ClassDecl.h"
#include "InterfaceDecl.h"

namespace SyntaxTree {
    class Decl : public Node {
    };

    class DeclToVariableDecl : public Decl {
    private:
        VariableDecl *variableDecl;
    public:
        void handleClassHierarchy() override;

        void handleScope() override;

        Cgen cgen() override;

        VariableDecl *getVariableDecl() const;

        void setVariableDecl(VariableDecl *variableDecl);
    };

    class DeclToFunctionDecl : public Decl {
    private:
        FunctionDecl *functionDecl;
    public:
        void handleClassHierarchy() override;

        void handleScope() override;

        Cgen cgen() override;

        FunctionDecl *getFunctionDecl() const;

        void setFunctionDecl(FunctionDecl *functionDecl);

    };

    class DeclToClassDecl : public Decl {
    private:
        ClassDecl *classDecl;
    public:
        Cgen cgen() override;

        void handleClassHierarchy() override;

        void handleScope() override;

        ClassDecl *getClassDecl() const;

        void setClassDecl(ClassDecl *classDecl);
    };

    class DeclToInterfaceDecl : public Decl {
    private:
        InterfaceDecl *interfaceDecl;
    public:
        void handleClassHierarchy() override;

        InterfaceDecl *getInterfaceDecl() const;

        void setInterfaceDecl(InterfaceDecl *interfaceDecl);
    };
}

#endif //DECAFCOMPILER_DECL_H
