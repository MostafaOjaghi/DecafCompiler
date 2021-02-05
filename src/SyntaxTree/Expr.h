//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_EXPR_H
#define DECAFCOMPILER_EXPR_H

#include <SymbolTable/TypeName.h>
#include "Node.h"

namespace SyntaxTree {
    class Expr : public Node {

    public:
        SymbolTable::TypeName type;
    };

    class AssignmentExpr : public Expr {
    };

    class Constant : public Expr {
    };

    class LValue : public Expr {
    };

    class ThisExpr : public Expr {
    };

    class Call : public Expr {
    };

    class ParenthesisExpr : public Expr {
    };

    class AddExpr : public Expr {
    };

    class SubExpr : public Expr {
    };

    class MultExpr : public Expr {
    };

    class DivExpr : public Expr {
    };

    class ModExpr : public Expr {
    };

    class NegExpr : public Expr {
    };

}

#endif //DECAFCOMPILER_EXPR_H
