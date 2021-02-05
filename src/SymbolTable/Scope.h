//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_SCOPE_H
#define DECAFCOMPILER_SCOPE_H


#include <string>

namespace SymbolTable {
    class Scope {
    private:
        std::string name;
        Scope *par;
    public:
        std::string getName();
        Scope * getPar();
    };
}


#endif //DECAFCOMPILER_SCOPE_H
