//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_IMPLEMENTS_H
#define DECAFCOMPILER_IMPLEMENTS_H

#include "Node.h"

namespace SyntaxTree {
    class Implements : public Node {
    private:
        std::vector<std::string>interfaceIds;
    public:
        const std::vector<std::string> &getInterfaceIds() const;
        void addInterfaceId(const std::string &interfaceId);
    };
}


#endif //DECAFCOMPILER_IMPLEMENTS_H
