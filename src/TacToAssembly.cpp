//
// Created by mostafa on 2/8/21.
//

#include "TacToAssembly.h"

#define TAC_TO_ASSEMBLY_IN_PROJECT
#include "../TAC_to_assembly/Function_Call.cpp"

std::string TacToAssembly::toAssembly(const std::string& tac) {
    stringstream stream;
    stream << tac;
    return tacToAssembly(stream);
}
