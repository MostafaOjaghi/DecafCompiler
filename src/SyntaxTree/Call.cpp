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
    cgen.append("Popparams " + std::to_string(4 * actuals->getExpressions().size()) + "\n");
    return cgen;
}

void SyntaxTree::CallToFunctionCall::handleScope() {
    actuals->setScope(getScope());
    actuals->handleScope();
}

std::string SyntaxTree::CallToMethodCall::getMethodIdent() const {
    return methodIdent;
}

void SyntaxTree::CallToMethodCall::setMethodIdent(std::string methodIdent) {
    CallToMethodCall::methodIdent = methodIdent;
}

SyntaxTree::Actuals *SyntaxTree::CallToMethodCall::getActuals() const {
    return actuals;
}

void SyntaxTree::CallToMethodCall::setActuals(SyntaxTree::Actuals *actuals) {
    CallToMethodCall::actuals = actuals;
}

SyntaxTree::Expr *SyntaxTree::CallToMethodCall::getObject() const {
    return object;
}

void SyntaxTree::CallToMethodCall::setObject(SyntaxTree::Expr *object) {
    CallToMethodCall::object = object;
}

SyntaxTree::Cgen SyntaxTree::CallToMethodCall::cgen() {
    Cgen cgen;
    Cgen object_cgen = object->cgen();
    Cgen actuals_cgen = actuals->cgen();
    if (object_cgen.typeName.isArray()) {
        if (methodIdent == "length" && actuals->getExpressions().empty()) {
            cgen.append(object_cgen);
            cgen.createVar("int", 0);
//            cgen.append("Assign " + cgen.var + " = &(" + object_cgen.var + ")\n");
            cgen.append("Load " + cgen.var + " = *(" + object_cgen.var + ")\n");
        } else
            assert(0); // TODO semantic error
    } else
        assert(0); // Not implemented yet
    return cgen;
}

void SyntaxTree::CallToMethodCall::handleScope() {
    object->setScope(getScope());
    object->handleScope();
    actuals->setScope(getScope());
    actuals->handleScope();
}
