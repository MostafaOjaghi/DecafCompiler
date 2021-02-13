//
// Created by mostafa on 2/5/21.
//

#ifndef DECAFCOMPILER_PROGRAMNODE_H
#define DECAFCOMPILER_PROGRAMNODE_H


#include "Node.h"

namespace SyntaxTree {
    class Decl;

    class ProgramNode : public Node {
    private:
        std::vector<Decl *> declerations;
    public:
        void handleClassHierarchy() override;

        Cgen cgen() override;

        void handleScope() override;

        void addDecl(Decl *decl);
    };
}

#endif //DECAFCOMPILER_PROGRAMNODE_H
