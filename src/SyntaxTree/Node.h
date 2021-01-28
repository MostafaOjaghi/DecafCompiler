//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


class Node {

public:
    virtual void cgen() = 0;
};

class ProgramNode : public Node {
public:
	virtual void cgen() {};
	virtual void addDecl(Node *node) {};
};


#endif //DECAFCOMPILER_NODE_H
