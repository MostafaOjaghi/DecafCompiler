//
// Created by shengdebao on 2/5/21.
//

#include "Call.h"
#include "Actuals.h"

SyntaxTree::Actuals *SyntaxTree::Call::getActuals() const {
    return actuals;
}

void SyntaxTree::Call::setActuals(SyntaxTree::Actuals *actuals) {
    Call::actuals = actuals;
}

const std::string &SyntaxTree::Call::getId() const {
    return id;
}

void SyntaxTree::Call::setId(const std::string &id) {
    Call::id = id;
}

SyntaxTree::Cgen SyntaxTree::CallToFunctionCall::cgen() {
    Cgen cgen;
    Cgen actualsCgen = actuals->cgen();
    cgen.append(actualsCgen);
    SymbolTable::SymbolTableEntry *entry = getScope()->getFunction(id);
    cgen.createVar(entry->getTypeName());
    if (entry->isField()) {
        SymbolTable::ClassType *classType = getScope()->getParentClass();
        cgenMethodCall(cgen, classType, "this");
    } else {
        std::string function_id = entry->getUniqueId();
        cgen.append("Lcall " + function_id + " -> " + cgen.var + "\n");
        cgen.append("Popparams " + std::to_string(actuals->getExpressions().size()) + "\n");
    }
    return cgen;
}

void SyntaxTree::CallToFunctionCall::handleScope() {
    actuals->setScope(getScope());
    actuals->handleScope();
}

SyntaxTree::Expr *SyntaxTree::CallToMethodCall::getExpr() const {
    return expr;
}

void SyntaxTree::CallToMethodCall::setExpr(SyntaxTree::Expr *expr) {
    CallToMethodCall::expr = expr;
}

SyntaxTree::Cgen SyntaxTree::CallToMethodCall::cgen() {
    Cgen cgen;
    Cgen expr_cgen = expr->cgen();
    Cgen actuals_cgen = actuals->cgen();
    cgen.append(expr_cgen);
    if (expr_cgen.typeName.isArray()) {
        if (id == "length" && actuals->getExpressions().empty()) {
            cgen.createVar("int", 0);
//            cgen.append("Assign " + cgen.var + " = &(" + object_cgen.var + ")\n");
            cgen.append("Load " + cgen.var + " = *(" + expr_cgen.var + ")\n");
        } else {
            SymbolTable::TypeName::semanticError();
        }
    } else {
        auto classType = SymbolTable::ClassType::getClass(expr_cgen.typeName.getId());
        std::string object_var = expr_cgen.var;

        cgenMethodCall(cgen, classType, object_var);

    }
    return cgen;
}

void SyntaxTree::Call::cgenMethodCall(SyntaxTree::Cgen &cgen, SymbolTable::ClassType *classType,
                                      const std::string &object_var) const {
    SymbolTable::SymbolTableEntry *method_entry = classType->getScope()->getFunction(this->getId());
    int methodPosition = classType->getMethodPosition(this->getId());

    cgen.createVar("int", 0);
    std::string tmpVar = cgen.var;
    cgen.createVar(method_entry->getTypeName());
    cgen.append("Load " + cgen.var + " = *(" + object_var + " + 0)\n");
    cgen.append("Load " + tmpVar + " = *(" + cgen.var + " + 0)\n");
    cgen.append("Assign " + tmpVar + " = " + object_var + " + " + tmpVar + "\n");
    cgen.append("Load " + cgen.var + " = *(" + cgen.var + " + " + std::to_string(methodPosition) + ")\n");
    cgen.append(this->getActuals()->cgen());
    cgen.append("Pushparam " + tmpVar + "\n");
    cgen.append("Acall " + cgen.var + " -> " + cgen.var + "\n");
    cgen.append("Popparams " + std::to_string((int) this->getActuals()->getExpressions().size() + 1) + "\n");
}

void SyntaxTree::CallToMethodCall::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
    this->getActuals()->setScope(this->getScope());
    this->getActuals()->handleScope();
}

void SyntaxTree::CallToMethodCall::handleClassHierarchy() {
    this->getExpr()->handleClassHierarchy();
    this->getActuals()->handleClassHierarchy();
}
