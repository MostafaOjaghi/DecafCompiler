//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_ACCESSMODE_H
#define DECAFCOMPILER_ACCESSMODE_H

#include "Node.h"

namespace SyntaxTree {
    class AccessMode : public Node {
    private:
        std::string accessModeId;
    public:
        const std::string &getAccessModeId() const;

        void setAccessModeId(const std::string &accessModeId);
    };
}


#endif //DECAFCOMPILER_ACCESSMODE_H
