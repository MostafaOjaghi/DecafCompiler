//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_PROTOTYPES_H
#define DECAFCOMPILER_PROTOTYPES_H

#include "Node.h"
#include "Prototype.h"

namespace SyntaxTree {
    class Prototypes : public Node {
    private:
        std::vector<Prototype *>prototypes;
    public:
        const std::vector<Prototype *> &getPrototypes() const;
        void addPrototype(Prototype * prototype);
    };
}


#endif //DECAFCOMPILER_PROTOTYPES_H
