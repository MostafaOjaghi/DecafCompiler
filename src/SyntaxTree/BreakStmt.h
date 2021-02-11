//
// Created by shengdebao on 2/5/21.
//

#ifndef DECAFCOMPILER_BREAKSTMT_H
#define DECAFCOMPILER_BREAKSTMT_H


#include "Node.h"

namespace SyntaxTree {
    class BreakStmt : public Node {
    public:
        Cgen cgen() override;
    };
}


#endif //DECAFCOMPILER_BREAKSTMT_H
