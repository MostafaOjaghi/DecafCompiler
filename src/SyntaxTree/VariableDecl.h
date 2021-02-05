//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_VARIABLEDECL_H
#define DECAFCOMPILER_VARIABLEDECL_H


#include "Node.h"
namespace SyntaxTree {
    class VariableDecl : public Node {
    };

    class VariableDeclToVariable : public VariableDecl {
    };
}

#endif //DECAFCOMPILER_VARIABLEDECL_H
