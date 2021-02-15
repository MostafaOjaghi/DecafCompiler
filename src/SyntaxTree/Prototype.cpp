//
// Created by shengdebao on 2/5/21.
//

#include "Prototype.h"

const std::string &SyntaxTree::PrototypeToTypeIdent::getPrototypeDeclId() const {
    return prototypeDeclId;
}

void SyntaxTree::PrototypeToTypeIdent::setPrototypeDeclId(const std::string &prototypeDeclId) {
    PrototypeToTypeIdent::prototypeDeclId = prototypeDeclId;
}

SyntaxTree::Formals *SyntaxTree::PrototypeToTypeIdent::getFormals() const {
    return formals;
}

void SyntaxTree::PrototypeToTypeIdent::setFormals(SyntaxTree::Formals *formals) {
    PrototypeToTypeIdent::formals = formals;
}

SyntaxTree::Type *SyntaxTree::PrototypeToTypeIdent::getType() const {
    return type;
}

void SyntaxTree::PrototypeToTypeIdent::setType(SyntaxTree::Type *type) {
    PrototypeToTypeIdent::type = type;
}

void SyntaxTree::PrototypeToTypeIdent::handleClassHierarchy() {
    this->getType()->handleClassHierarchy();
    this->getFormals()->handleClassHierarchy();
}

SyntaxTree::Cgen SyntaxTree::PrototypeToTypeIdent::cgen() {
    // TODO: SHOULD BE IMPLEMENTED
    return Node::cgen();
}

void SyntaxTree::PrototypeToTypeIdent::handleScope() {
    // TODO: SHOULD BE IMPLEMENTED
    Node::handleScope();
}

const std::string &SyntaxTree::PrototypeToVoid::getPrototypeDeclId() const {
    return prototypeDeclId;
}

void SyntaxTree::PrototypeToVoid::setPrototypeDeclId(const std::string &prototypeDeclId) {
    PrototypeToVoid::prototypeDeclId = prototypeDeclId;
}

SyntaxTree::Formals *SyntaxTree::PrototypeToVoid::getFormals() const {
    return formals;
}

void SyntaxTree::PrototypeToVoid::setFormals(SyntaxTree::Formals *formals) {
    PrototypeToVoid::formals = formals;
}

void SyntaxTree::PrototypeToVoid::handleClassHierarchy() {
    this->getFormals()->handleClassHierarchy();
}

SyntaxTree::Cgen SyntaxTree::PrototypeToVoid::cgen() {
    // TODO: SHOULD BE IMPLEMENTED
    return Node::cgen();
}

void SyntaxTree::PrototypeToVoid::handleScope() {
    // TODO: SHOULD BE IMPLEMENTED
    Node::handleScope();
}
