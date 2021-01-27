//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_RESULTTYPE_H
#define DECAFCOMPILER_RESULTTYPE_H
#include <string>


class Type {

    static vector <Type> types;
    Type *parent;
    bool isPrimitive;
    string id;
};


#endif //DECAFCOMPILER_RESULTTYPE_H
