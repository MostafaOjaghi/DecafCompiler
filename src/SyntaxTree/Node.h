//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


#include <vector>
namespace SyntaxTree {
    class Decl;

    class Node {

    public:
        virtual void cgen() = 0;
    };

    class ProgramNode : public Node {
    private:
        std::vector<Decl *> declerations;
    public:
        virtual void cgen() {};

        virtual void addDecl(Decl *decl);
    };
}
#endif //DECAFCOMPILER_NODE_H
