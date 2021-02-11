//
// Created by mostafa on 2/7/21.
//

#ifndef DECAFCOMPILER_UNIQUEGENERATOR_H
#define DECAFCOMPILER_UNIQUEGENERATOR_H


#include <string>

class UniqueGenerator {
public:
    static std::string newTemp();
    static std::string newLabel();
};


#endif //DECAFCOMPILER_UNIQUEGENERATOR_H
