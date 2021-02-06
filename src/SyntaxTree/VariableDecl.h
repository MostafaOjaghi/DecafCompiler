//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_VARIABLEDECL_H
#define DECAFCOMPILER_VARIABLEDECL_H


#include "Node.h"
#include "Variable.h"

namespace SyntaxTree {
    class VariableDecl : public Node {
    private:
        Variable *variable;
    public:
        Variable *getVariable() const;

        void setVariable(Variable *variable);

        Cgen cgen() override;
    };
}

#endif //DECAFCOMPILER_VARIABLEDECL_H
