//
// Created by mostafa on 2/5/21.
//

#ifndef DECAFCOMPILER_PRINTSTMT_H
#define DECAFCOMPILER_PRINTSTMT_H


#include "Node.h"
#include "Expr.h"
#include "Actuals.h"

namespace SyntaxTree {

    class PrintStmt : public Node {
    private:
        Actuals *actuals;

    public:
        void handleClassHierarchy() override;

        Actuals *getActuals() const;

        void setActuals(Actuals *actuals);

        Cgen cgen() override;

        void handleScope() override;
    };
}

#endif //DECAFCOMPILER_PRINTSTMT_H
