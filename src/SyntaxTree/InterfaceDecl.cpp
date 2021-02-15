//
// Created by shengdebao on 2/5/21.
//

#include "InterfaceDecl.h"

const std::string &SyntaxTree::InterfaceDecl::getInterfaceId() const {
    return interfaceId;
}

void SyntaxTree::InterfaceDecl::setInterfaceId(const std::string &interfaceId) {
    InterfaceDecl::interfaceId = interfaceId;
}

SyntaxTree::Prototypes *SyntaxTree::InterfaceDecl::getPrototypes() const {
    return prototypes;
}

void SyntaxTree::InterfaceDecl::setPrototypes(SyntaxTree::Prototypes *prototypes) {
    InterfaceDecl::prototypes = prototypes;
}

void SyntaxTree::InterfaceDecl::handleClassHierarchy() {
    this->getPrototypes()->handleClassHierarchy();
}

SyntaxTree::Cgen SyntaxTree::InterfaceDecl::cgen() {
    // TODO: SHOULD BE IMPLEMENTED
    return Node::cgen();
}

void SyntaxTree::InterfaceDecl::handleScope() {
    // TODO: SHOULD BE IMPLEMENTED
    Node::handleScope();
}
