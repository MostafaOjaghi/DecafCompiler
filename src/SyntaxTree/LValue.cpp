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
    SymbolTable::SymbolTableEntry *entry = getScope()->getEntry(id);
    cgen.var = entry->getUniqueId();
    cgen.typeName = entry->getTypeName();
    // TODO check: may need to define new temp: maybe the following code
//    if (cgen.typeName.isArray()){
//        std::cout << id << ": " << entry->getTypeName().getDimension() << std::endl;
//        cgen.createVar(cgen.typeName.getId(), cgen.typeName.getDimension());
//        cgen.append("Assign " + cgen.var + " = " + entry->getUniqueId() + "\n");
//    } else if (cgen.typeName.isPrimitive()) {
//        cgen.var = entry->getUniqueId();
//    } else
//        assert(0); // TODO handle other types
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

SyntaxTree::Cgen SyntaxTree::LValueToFieldAccess::cgen() {
    Cgen cgenExpr = this->getExpr()->cgen(), cgen;
    auto classType = SymbolTable::ClassType::getClass(cgenExpr.typeName.getId());
    std::cout << "classType: " << classType << std::endl;

    auto entry = classType->getScope()->getEntry(this->getId(), this->getScope());
    std::cout << "get entry done!" << std::endl;

    int pos = classType->getIndexInObjectLayout(this->getId());
    std::cout << "get index done!" << std::endl;

    cgen.append(cgenExpr);
    std::cout << "cgen append!" << std::endl;

    cgen.createVar(entry->getTypeName());
    cgen.append("Load " + cgen.var + " = *(" + cgenExpr.var + " + " + std::to_string(pos) + ")\n");
    return cgen;
}

void SyntaxTree::LValueToFieldAccess::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
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
    cgen.append("Assign " + cgen.var + " = " + index.var + " + 1\n");
    cgen.append("Assign " + cgen.var + " = " + cgen.var + " * 4\n");
    cgen.append("Assign " + cgen.var + " = " + name.var + " + " + cgen.var + "\n");
    return cgen;
}

void SyntaxTree::LValueToArray::handleScope() {
    exprArrayName->setScope(getScope());
    exprArrayName->handleScope();
    exprArrayIndex->setScope(getScope());
    exprArrayIndex->handleScope();
}
