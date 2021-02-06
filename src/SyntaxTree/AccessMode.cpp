//
// Created by shengdebao on 2/5/21.
//

#include "AccessMode.h"

const std::string &SyntaxTree::AccessMode::getAccessModeId() const {
    return accessModeId;
}

void SyntaxTree::AccessMode::setAccessModeId(const std::string &accessModeId) {
    AccessMode::accessModeId = accessModeId;
}
