//
// Created by shengdebao on 2/5/21.
//

#include "Implements.h"

const std::vector<std::string> &SyntaxTree::Implements::getInterfaceIds() const {
    return interfaceIds;
}

void SyntaxTree::Implements::addInterfaceId(const std::string &interfaceId) {
    interfaceIds.push_back(interfaceId);
}
