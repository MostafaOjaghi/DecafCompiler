//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


class Node {

public:
    virtual void cgen() = 0;
};


#endif //DECAFCOMPILER_NODE_H
