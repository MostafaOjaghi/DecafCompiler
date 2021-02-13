//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <SymbolTable/Scope.h>
#include "SymbolTable/UniqueGenerator.h"


namespace SyntaxTree {
    class Cgen {
    public:
        explicit Cgen(std::string code);

        Cgen() = default;

        SymbolTable::TypeName typeName;
        std::string var;
        std::string code;
        int var_count = 0;

        std::vector<std::string> breakLabels;
        std::vector<std::string> continueLabels;

        void append(Cgen cgen);
        void append(std::string code);
        void createVar(const std::string &typeId, int dimension);
        void createVar(SymbolTable::TypeName typeName1);
        void addBreakLabel(std::string label);
        void addContinueLabel(std::string label);
        std::string getBreakLabels();
        std::string getContinueLabels();
    };

    class Node {
    private:
        SymbolTable::Scope *scope = nullptr;
    public:
        virtual void handleClassHierarchy() {};
        void setScope(SymbolTable::Scope *scope);
        virtual Cgen cgen() {return Cgen();};
        SymbolTable::Scope *getScope();
        virtual void handleScope() {};
    };
}
#endif //DECAFCOMPILER_NODE_H
