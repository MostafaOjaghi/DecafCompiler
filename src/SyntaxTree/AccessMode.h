//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_ACCESSMODE_H
#define DECAFCOMPILER_ACCESSMODE_H

#include "Node.h"

namespace SyntaxTree {
    class AccessMode : public Node {
    private:
        SymbolTable::AccessMode accessMode;
    public:
        void handleScope() override;

    public:
        SymbolTable::AccessMode getAccessMode() const;

        void setAccessMode(SymbolTable::AccessMode accessMode);
    };
}


#endif //DECAFCOMPILER_ACCESSMODE_H
