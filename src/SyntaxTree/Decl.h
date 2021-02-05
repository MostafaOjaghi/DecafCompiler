//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_DECL_H
#define DECAFCOMPILER_DECL_H


#include "Node.h"
namespace SyntaxTree {
    class Decl : public Node {
    };

    class DeclToVariableDecl : public Decl {
    };

    class DeclToFunctionDecl : public Decl {
    };

    class DeclToInterfaceDecl : public Decl {
    };
}

#endif //DECAFCOMPILER_DECL_H
