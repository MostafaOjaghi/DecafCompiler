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
