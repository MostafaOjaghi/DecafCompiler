//
// Created by shengdebao on 2/5/21.
//

#include "Prototypes.h"

const std::vector<SyntaxTree::Prototype *> &SyntaxTree::Prototypes::getPrototypes() const {
    return prototypes;
}

void SyntaxTree::Prototypes::addPrototype(SyntaxTree::Prototype *prototype) {
    prototypes.push_back(prototype);
}

void SyntaxTree::Prototypes::handleClassHierarchy() {
    for (Prototype * prototype : prototypes) {
        prototype->handleClassHierarchy();
    }
}

SyntaxTree::Cgen SyntaxTree::Prototypes::cgen() {
    // TODO: SHOULD BE IMPLEMENTED
    return Node::cgen();
}

void SyntaxTree::Prototypes::handleScope() {
    // TODO: SHOULD BE IMPLEMENTED
    Node::handleScope();
}
