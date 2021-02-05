//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_NODE_H
#define DECAFCOMPILER_NODE_H


#include <vector>
#include <string>

class Decl;

class Node {

public:
    virtual std::string cgen() = 0;
};

class ProgramNode : public Node {
private:
    std::vector<Decl *> declerations;
public:
    virtual std::string cgen();

    virtual void addDecl(Decl *decl);
};

#endif //DECAFCOMPILER_NODE_H
