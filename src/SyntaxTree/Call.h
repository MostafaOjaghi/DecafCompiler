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

    };

    class CallToMethodCall : public Call {
    private:
        Expr *expr;
        std::string id;
    public:
        void handleClassHierarchy() override;

        const std::string &getId() const;

        void setId(const std::string &id);

    private:
        Actuals *actuals;
    public:
        Actuals *getActuals() const;

    public:
        Cgen cgen() override;

        void handleScope() override;

        Expr *getExpr() const;

        void setExpr(Expr *expr);


        void setActuals(Actuals *actuals);
    };

    class CallToFunctionCall : public Call {
    private:
        std::string functionId;
        Actuals *actuals;
    public:
        Cgen cgen() override;

        void handleScope() override;

        const std::string &getFunctionId() const;

        void setFunctionId(const std::string &functionId);

        Actuals *getActuals() const;

        void setActuals(Actuals *actuals);
    };
}


#endif //DECAFCOMPILER_CALL_H
