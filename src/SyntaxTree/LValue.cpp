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
    SymbolTable::SymbolTableEntry *entry = getScope()->getVariable(id);
    cgen.createVar(entry->getTypeName());
    if (entry->isField()) {
        auto classType = SymbolTable::ClassType::getClass(getScope()->getClassName());
        int pos = classType->getIndexInObjectLayout(this->getId());
        cgen.append("Assign " + cgen.var + " = this + " + std::to_string(pos * 4) + "\n");
    }
    else
        cgen.append("Addr " + cgen.var + " = &" + entry->getUniqueId() + "\n");
    return cgen;
}

void SyntaxTree::LValueToIdent::handleScope() {
    // Nothing here
}

void SyntaxTree::LValueToIdent::handleClassHierarchy() {
    // nothing to do
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

SyntaxTree::Cgen SyntaxTree::LValueToFieldAccess::cgen() {
    Cgen cgenExpr = this->getExpr()->cgen(), cgen;
    auto classType = SymbolTable::ClassType::getClass(cgenExpr.typeName.getId());
    auto entry = classType->getScope()->getVariable(this->getId(), this->getScope());
    int pos = classType->getIndexInObjectLayout(this->getId());
    cgen.append(cgenExpr);
    cgen.createVar(entry->getTypeName());
    cgen.append("Assign " + cgen.var + " = " + cgenExpr.var + " + " + std::to_string(pos * 4) + "\n");
    return cgen;
}

void SyntaxTree::LValueToFieldAccess::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
}

void SyntaxTree::LValueToFieldAccess::handleClassHierarchy() {
    this->getExpr()->handleClassHierarchy();
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
    if (index.typeName.getId() != "int")
        SymbolTable::TypeName::semanticError();
    cgen.createVar(name.typeName.getId(), name.typeName.getDimension() - 1);
    cgen.append("Assign " + cgen.var + " = " + index.var + " + 1\n");
    cgen.append("Assign " + cgen.var + " = " + cgen.var + " * 4\n");
    cgen.append("Assign " + cgen.var + " = " + name.var + " + " + cgen.var + "\n");
    if (index.typeName.getId() != "int" || index.typeName.getDimension() != 0)
        SymbolTable::TypeName::semanticError();
    return cgen;
}

void SyntaxTree::LValueToArray::handleScope() {
    exprArrayName->setScope(getScope());
    exprArrayName->handleScope();
    exprArrayIndex->setScope(getScope());
    exprArrayIndex->handleScope();
}

void SyntaxTree::LValueToArray::handleClassHierarchy() {
    this->getExprArrayIndex()->handleClassHierarchy();
    this->getExprArrayName()->handleClassHierarchy();
}
