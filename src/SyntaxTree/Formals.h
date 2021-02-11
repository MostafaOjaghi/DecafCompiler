//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FORMALS_H
#define DECAFCOMPILER_FORMALS_H

#include "Node.h"
#include "Variable.h"

namespace SyntaxTree {
    class Formals : public Node {
    private:
        std::vector<Variable *>variables;
    public:
        void handleScope() override;

        const std::vector<Variable *> &getVariables() const;

        void addVariable(Variable *variable);

        Cgen cgen() override;
    };

    class FormalsToVariablePlus : public Formals {

    };

    class FormalsToEpsilon : public Formals {

    };

}


#endif //DECAFCOMPILER_FORMALS_H
