//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_VARIABLEDECLS_H
#define DECAFCOMPILER_VARIABLEDECLS_H


#include <vector>
#include "VariableDecl.h"

namespace SyntaxTree {

    class VariableDecls : public Node {
    private:
        std::vector<VariableDecl *> variableDecls;
    public:
        void handleClassHierarchy() override;

        void handleScope() override;

        const std::vector<VariableDecl *> &getVariableDecls() const;
        void addVariableDecl(VariableDecl *variableDecl);

        Cgen cgen() override;
    };
}


#endif //DECAFCOMPILER_VARIABLEDECLS_H
