//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_CONTINUESTMT_H
#define DECAFCOMPILER_CONTINUESTMT_H

#include "Node.h"

namespace SyntaxTree {
    class ContinueStmt : public Node {
    public:
        Cgen cgen() override;
    };
}


#endif //DECAFCOMPILER_CONTINUESTMT_H
