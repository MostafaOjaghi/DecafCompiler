//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


#include <vector>
#include <string>
#include <SymbolTable/Scope.h>


namespace SyntaxTree {
    class Cgen {
    public:
        Cgen(std::string code);

        Cgen() = default;

        std::string var;
        std::string code;
    };

    class Node {
    private:
        SymbolTable::Scope *scope;

    public:
        virtual Cgen cgen() {return Cgen();};
        virtual SymbolTable::Scope * getScope();
        virtual void createScope() {};
    };
}
#endif //DECAFCOMPILER_NODE_H
