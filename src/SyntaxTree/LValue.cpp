//
// Created by shengdebao on 2/5/21.
//

#include "LValue.h"
#include "Expr.h"

const std::string &SyntaxTree::LValueToIdent::getId() const {
    return id;
}

void SyntaxTree::LValueToIdent::setId(const std::string &id) {
    LValueToIdent::id = id;
}

SyntaxTree::Cgen SyntaxTree::LValueToIdent::cgen() {
    Cgen cgen;
    // TODO check: may need to define new temp
    SymbolTable::SymbolTableEntry *entry = getScope()->getEntry(id);
    cgen.var = entry->getUniqueId();
    cgen.typeName = entry->getTypeName();
    return cgen;
}

void SyntaxTree::LValueToIdent::handleScope() {
    // Nothing here
}

SyntaxTree::Expr *SyntaxTree::LValueToFieldAccess::getExpr() const {
    return expr;
}

void SyntaxTree::LValueToFieldAccess::setExpr(SyntaxTree::Expr *expr) {
    LValueToFieldAccess::expr = expr;
}

const std::string &SyntaxTree::LValueToFieldAccess::getId() const {
    return id;
}

void SyntaxTree::LValueToFieldAccess::setId(const std::string &id) {
    LValueToFieldAccess::id = id;
}

SyntaxTree::Expr *SyntaxTree::LValueToArray::getExprArrayName() const {
    return exprArrayName;
}

void SyntaxTree::LValueToArray::setExprArrayName(SyntaxTree::Expr *exprArrayName) {
    LValueToArray::exprArrayName = exprArrayName;
}

SyntaxTree::Expr *SyntaxTree::LValueToArray::getExprArrayIndex() const {
    return exprArrayIndex;
}

void SyntaxTree::LValueToArray::setExprArrayIndex(SyntaxTree::Expr *exprArrayIndex) {
    LValueToArray::exprArrayIndex = exprArrayIndex;
}

SyntaxTree::Cgen SyntaxTree::LValueToArray::cgen() {
    Cgen cgen;
    Cgen name = exprArrayName->cgen();
    Cgen index = exprArrayIndex->cgen();
    cgen.append(name);
    cgen.append(index);
    cgen.createVar("int", 0); // TODO int?
    cgen.append("Addr " + cgen.var + " = &(" + name.var + " + " + index.var + ")\n");
    return cgen;
}

void SyntaxTree::LValueToArray::handleScope() {
    exprArrayName->setScope(getScope());
    exprArrayName->handleScope();
    exprArrayIndex->setScope(getScope());
    exprArrayIndex->handleScope();
}
