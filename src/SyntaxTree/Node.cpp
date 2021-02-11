//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "Node.h"

#include <utility>

SymbolTable::Scope * SyntaxTree::Node::getScope() {return scope;}

void SyntaxTree::Node::setScope(SymbolTable::Scope *scope) {
    Node::scope = scope;
}

SyntaxTree::Cgen::Cgen(std::string code) : code(std::move(code)) {}

void SyntaxTree::Cgen::append(SyntaxTree::Cgen cgen) {
    code += cgen.code;
    var_count += cgen.var_count;
    breakLabels.insert(breakLabels.end(), cgen.breakLabels.begin(), cgen.breakLabels.end());
    continueLabels.insert(continueLabels.end(), cgen.continueLabels.begin(), cgen.continueLabels.end());
}

void SyntaxTree::Cgen::append(std::string code) {
    Cgen::code += code;
}

void SyntaxTree::Cgen::addBreakLabel(std::string label) {
    breakLabels.push_back(label);
}

void SyntaxTree::Cgen::addContinueLabel(std::string label) {
    continueLabels.push_back(label);
}

std::string SyntaxTree::Cgen::getBreakLabels() {
    std::string st;
    for (const std::string &label : breakLabels)
        st += "Label " + label + ":\n";
    breakLabels.clear();
    return st;
}

std::string SyntaxTree::Cgen::getContinueLabels() {
    std::string st;
    for (const std::string &label : continueLabels)
        st += "Label " + label + ":\n";
    continueLabels.clear();
    return st;
}

void SyntaxTree::Cgen::createVar(const std::string &typeId, int dimension) {
    var = UniqueGenerator::newTemp();
    var_count += 1;
    typeName = SymbolTable::TypeName(typeId, dimension);
}
