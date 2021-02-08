//
// Created by mostafa on 2/7/21.
//

#include "UniqueGenerator.h"

std::string UniqueGenerator::newTemp() {
    static int n = 0;
    return "_t" + std::to_string(n++);
}

std::string UniqueGenerator::newLabel() {
    static int n = 0;
    return "_l" + std::to_string(n++);
}
