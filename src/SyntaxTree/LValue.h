//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_LVALUE_H
#define DECAFCOMPILER_LVALUE_H

#include "Node.h"

namespace SyntaxTree {
    class Expr;

    class LValue : public Node {

    };

    class LValueToIdent : public LValue {
    private:
        std::string id;
    public:
        Cgen cgen() override;

        void handleScope() override;

        const std::string &getId() const;

        void setId(const std::string &id);
    };


    class LValueToFieldAccess : public LValue {
    private:
        Expr *expr;
        std::string id;
    public:
        void handleScope() override;

        Cgen cgen() override;

        Expr *getExpr() const;

        void setExpr(Expr *expr);

        const std::string &getId() const;

        void setId(const std::string &id);
    };

    class LValueToArray : public LValue {
    private:
        Expr *exprArrayName;
        Expr *exprArrayIndex;
    public:
        Cgen cgen() override;

        void handleScope() override;

        Expr *getExprArrayName() const;

        void setExprArrayName(Expr *exprArrayName);

        Expr *getExprArrayIndex() const;

        void setExprArrayIndex(Expr *exprArrayIndex);
    };

}


#endif //DECAFCOMPILER_LVALUE_H
