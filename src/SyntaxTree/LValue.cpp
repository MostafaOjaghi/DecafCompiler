//
// Created by shengdebao on 2/5/21.
//

#include "LValue.h"

const std::string &SyntaxTree::LValueToIdent::getId() const {
    return id;
}

void SyntaxTree::LValueToIdent::setId(const std::string &id) {
    LValueToIdent::id = id;
}

SyntaxTree::Cgen SyntaxTree::LValueToIdent::cgen() {
    Cgen cgen;
    // TODO check: may need to define new temp
    cgen.var = getScope()->getEntry(id)->getUniqueId();
    cgen.var_count += 1;
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
