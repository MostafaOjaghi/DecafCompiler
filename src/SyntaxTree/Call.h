//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_CALL_H
#define DECAFCOMPILER_CALL_H

#include "Node.h"
#include "Expr.h"

namespace SyntaxTree {
    class Actuals;

    class Call : public Node {
    protected:
        Actuals *actuals;
        std::string id;

        void cgenMethodCall(SyntaxTree::Cgen &cgen, SymbolTable::ClassType *classType,
                            const std::string &object_var) const;

    public:
        Actuals *getActuals() const;

        void setActuals(Actuals *actuals);

        const std::string &getId() const;

        void setId(const std::string &id);
    };

    class CallToMethodCall : public Call {
    private:
        Expr *expr;
    public:
        void handleClassHierarchy() override;

    public:
        Cgen cgen() override;

        void handleScope() override;

        Expr *getExpr() const;

        void setExpr(Expr *expr);
    };

    class CallToFunctionCall : public Call {
    public:
        Cgen cgen() override;

        void handleScope() override;
    };
}


#endif //DECAFCOMPILER_CALL_H
