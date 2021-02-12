//
// Created by shengdebao on 2/5/21.
//

#include "Call.h"
#include "Actuals.h"

const std::string &SyntaxTree::CallToFunctionCall::getFunctionId() const {
    return functionId;
}

void SyntaxTree::CallToFunctionCall::setFunctionId(const std::string &functionId) {
    CallToFunctionCall::functionId = functionId;
}

SyntaxTree::Actuals *SyntaxTree::CallToFunctionCall::getActuals() const {
    return actuals;
}

void SyntaxTree::CallToFunctionCall::setActuals(SyntaxTree::Actuals *actuals) {
    CallToFunctionCall::actuals = actuals;
}

SyntaxTree::Cgen SyntaxTree::CallToFunctionCall::cgen() {
    // TODO handle return type
    Cgen cgen;
    Cgen actualsCgen = actuals->cgen();
    cgen.append(actualsCgen);
    cgen.createVar("int", 0);
    cgen.append("Lcall func_" + functionId + " -> " + cgen.var + "\n");
    // TODO: 4 * should be removed
    cgen.append("Popparams " + std::to_string(4 * actuals->getExpressions().size()) + "\n");
    return cgen;
}

void SyntaxTree::CallToFunctionCall::handleScope() {
    actuals->setScope(getScope());
    actuals->handleScope();
}



void SyntaxTree::CallToMethodCall::setActuals(SyntaxTree::Actuals *actuals) {
    CallToMethodCall::actuals = actuals;
}

const std::string &SyntaxTree::CallToMethodCall::getId() const {
    return Id;
}

void SyntaxTree::CallToMethodCall::setId(const std::string &id) {
    Id = id;
}

SyntaxTree::Expr *SyntaxTree::CallToMethodCall::getExpr() const {
    return expr;
}

void SyntaxTree::CallToMethodCall::setExpr(SyntaxTree::Expr *expr) {
    CallToMethodCall::expr = expr;
}

SyntaxTree::Cgen SyntaxTree::CallToMethodCall::cgen() {
    Cgen cgen;
    Cgen cgenExpr = this->getExpr()->cgen();
    cgen.append(cgenExpr);
    // TODO: return type should be set
    cgen.createVar("int", 0);
    std::string tmpVar = cgen.var;
    cgen.createVar("int", 0);
    cgen.append("Load " + cgen.var + " = *(" + cgenExpr.var + " + 0)\n");
    auto classType = SymbolTable::ClassType::getClass(cgenExpr.typeName.getId());
    int funcPos =classType->getFunctionPosition(this->getId());
    cgen.append("Load " + tmpVar + " = *(" + cgen.var + " + 0)\n");
    cgen.append("Load " + tmpVar + " = *(" + cgenExpr.var + " + " + tmpVar + ")\n");
    cgen.append("Load " + cgen.var + " = *(" + cgen.var + " + " + std::to_string(funcPos) + ")\n");
    cgen.append(this->getActuals()->cgen());
    cgen.append("Pushparam " + tmpVar + "\n");
    cgen.append("Acall " + cgen.var + " -> " + cgen.var + "\n");
    cgen.append("Popparams " + std::to_string((int) this->getActuals()->getExpressions().size() + 1) + "\n");

    return cgen;
}

void SyntaxTree::CallToMethodCall::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
    this->getActuals()->setScope(this->getScope());
    this->getActuals()->handleScope();
}

SyntaxTree::Actuals *SyntaxTree::CallToMethodCall::getActuals() const {
    return actuals;
}
