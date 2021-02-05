//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


#include <vector>
#include <string>
#include <SymbolTable/Scope.h>


namespace SyntaxTree {
    class Decl;

    class Node {
    private:
        SymbolTable::Scope *scope;

    public:
        virtual std::string cgen() = 0;
        virtual SymbolTable::Scope * getScope();
        virtual void createScope()  {};
    };

    class ProgramNode : public Node {
    private:
        std::vector<Decl *> declerations;
    public:
        virtual std::string cgen() {};

        virtual void addDecl(Decl *decl);
    };
}
#endif //DECAFCOMPILER_NODE_H
