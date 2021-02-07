//
// Created by mostafa on 2/7/21.
//

#include "TemporaryGenerator.h"

std::string TemporaryGenerator::newTemp() {
    static int n = 0;
    return "_t" + std::to_string(n++);
}
