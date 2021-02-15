//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_FIELD_H
#define DECAFCOMPILER_FIELD_H

#include "Node.h"
#include "VariableDecl.h"
#include "AccessMode.h"
#include "FunctionDecl.h"

namespace SyntaxTree {
    class Field : public Node {

    };

    class FieldToVariableDecl : public Field {
    private:
        AccessMode * accessMode;
        VariableDecl * variableDecl;
    public:
        void handleScope() override;

        AccessMode *getAccessMode() const;

        void setAccessMode(AccessMode *accessMode);

        VariableDecl *getVariableDecl() const;

        void setVariableDecl(VariableDecl *variableDecl);
    };

    class FieldToFunctionDecl : public Field {
        AccessMode * accessMode;
        FunctionDecl *functionDecl;
    public:
        Cgen cgen() override;

        void handleScope() override;

        AccessMode *getAccessMode() const;

        void setAccessMode(AccessMode *accessMode);

        FunctionDecl *getFunctionDecl() const;

        void setFunctionDecl(FunctionDecl *functionDecl);
    };
}


#endif //DECAFCOMPILER_FIELD_H
