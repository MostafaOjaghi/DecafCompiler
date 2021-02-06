//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_EXTENDS_H
#define DECAFCOMPILER_EXTENDS_H

#include "Node.h"

namespace SyntaxTree {
    class Extends : public Node {
    private:
        std::string parentClassId;
    public:
        const std::string &getParentClassId() const;

        void setParentClassId(const std::string &parentClassId);
    };
}


#endif //DECAFCOMPILER_EXTENDS_H
