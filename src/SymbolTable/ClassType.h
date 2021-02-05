//
// Created by mostafa on 2/5/21.
//

#ifndef DECAFCOMPILER_CLASSTYPE_H
#define DECAFCOMPILER_CLASSTYPE_H

namespace SymbolTable {
    class ClassType {
        ClassType *parent;
    public:
        ClassType *getParent() const;
    };
}

#endif //DECAFCOMPILER_CLASSTYPE_H
