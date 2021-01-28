//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_RESULTTYPE_H
#define DECAFCOMPILER_RESULTTYPE_H
#include <string>
#include <vector>

class Type {

    static std::vector <Type> types;
    Type *parent;
    bool isPrimitive;
    std::string id;
};


#endif //DECAFCOMPILER_RESULTTYPE_H
