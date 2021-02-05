//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FUNCTIONDECL_H
#define DECAFCOMPILER_FUNCTIONDECL_H


#include "Node.h"

namespace SyntaxTree {

    class FunctionDecl : public Node {

    };

    class FunctionDeclToTypeIdent : public FunctionDecl {

    };

    class FunctionDeclToVoidIdent : public FunctionDecl {

    };
}

#endif //DECAFCOMPILER_FUNCTIONDECL_H
