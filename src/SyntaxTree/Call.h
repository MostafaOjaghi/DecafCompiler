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
        // TODO add missing field
        Expr *methodIdent;
        Actuals *actuals;
    public:
        Expr *getMethodIdent() const;

        void setMethodIdent(Expr *methodIdent);

        Actuals *getActuals() const;

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
