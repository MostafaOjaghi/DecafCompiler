//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "Expr.h"
#include "Type.h"
#include "Call.h"

SyntaxTree::LValue *SyntaxTree::ExprToAssignmentExpr::getLValue() const {
    return lValue;
}

void SyntaxTree::ExprToAssignmentExpr::setLValue(SyntaxTree::LValue *lValue) {
    ExprToAssignmentExpr::lValue = lValue;
}

SyntaxTree::Expr *SyntaxTree::ExprToAssignmentExpr::getExpr() const {
    return expr;
}

void SyntaxTree::ExprToAssignmentExpr::setExpr(SyntaxTree::Expr *expr) {
    ExprToAssignmentExpr::expr = expr;
}

void SyntaxTree::ExprToAssignmentExpr::handleScope() {
    this->getExpr()->setScope(this->getScope());
    this->getExpr()->handleScope();
    this->getLValue()->setScope(this->getScope());
    this->getLValue()->handleScope();
}

SyntaxTree::Cgen SyntaxTree::ExprToAssignmentExpr::cgen() { // TODO handle lvalue correctly
    Cgen cgen;
    Cgen lvalue_cgen = lValue->cgen();
    Cgen expr_cgen = expr->cgen();
    cgen.append(expr_cgen);
    cgen.append(lvalue_cgen);
//    if (dynamic_cast<LValueToIdent *>(lValue))
//        cgen.append("Assign " + lvalue_cgen.var + " = " + expr_cgen.var + "\n");
//    else
        cgen.append("Store *(" + lvalue_cgen.var + ") = " + expr_cgen.var + "\n");
    return cgen;
}

SyntaxTree::Constant *SyntaxTree::ExprToConstant::getConstant() const {
    return constant;
}

void SyntaxTree::ExprToConstant::setConstant(SyntaxTree::Constant *constant) {
    ExprToConstant::constant = constant;
}

void SyntaxTree::ExprToConstant::handleScope() {
    this->getConstant()->setScope(this->getScope());
    this->getConstant()->handleScope();
}

SyntaxTree::Cgen SyntaxTree::ExprToConstant::cgen() {
    return constant->cgen();
}

SyntaxTree::LValue *SyntaxTree::ExprToLValue::getLValue() const {
    return lValue;
}

void SyntaxTree::ExprToLValue::setLValue(SyntaxTree::LValue *lValue) {
    ExprToLValue::lValue = lValue;
}

SyntaxTree::Cgen SyntaxTree::ExprToLValue::cgen() {
//    if (dynamic_cast<LValueToIdent *>(lValue))
//        return lValue->cgen();
    Cgen cgen;
    Cgen lvalue_cgen = lValue->cgen();
    cgen.append(lvalue_cgen);
    cgen.createVar(lvalue_cgen.typeName.getId(), lvalue_cgen.typeName.getDimension());
    cgen.append("Load " + cgen.var + " = *(" + lvalue_cgen.var + ")\n");
    return cgen;
}

void SyntaxTree::ExprToLValue::handleScope() {
    lValue->setScope(getScope());
    lValue->handleScope();
}

SyntaxTree::Call *SyntaxTree::ExprToCall::getCall() const {
    return call;
}

void SyntaxTree::ExprToCall::setCall(SyntaxTree::Call *call) {
    ExprToCall::call = call;
}

SyntaxTree::Cgen SyntaxTree::ExprToCall::cgen() {
    return call->cgen();
}

void SyntaxTree::ExprToCall::handleScope() {
    call->setScope(getScope());
    call->handleScope();
}

SyntaxTree::Expr *SyntaxTree::ExprToParenthesisExpr::getExpr() const {
    return expr;
}

void SyntaxTree::ExprToParenthesisExpr::setExpr(SyntaxTree::Expr *expr) {
    ExprToParenthesisExpr::expr = expr;
}

SyntaxTree::Cgen SyntaxTree::ExprToParenthesisExpr::cgen() {
    return expr->cgen();
}

void SyntaxTree::ExprToParenthesisExpr::handleScope() {
    expr->setScope(getScope());
    expr->handleScope();
}

SyntaxTree::Expr *SyntaxTree::ExprToBinaryOperation::getOperand1() const {
    return operand1;
}

void SyntaxTree::ExprToBinaryOperation::setOperand1(SyntaxTree::Expr *operand1) {
    ExprToBinaryOperation::operand1 = operand1;
}

SyntaxTree::Expr *SyntaxTree::ExprToBinaryOperation::getOperand2() const {
    return operand2;
}

void SyntaxTree::ExprToBinaryOperation::setOperand2(SyntaxTree::Expr *operand2) {
    ExprToBinaryOperation::operand2 = operand2;
}

const std::string &SyntaxTree::ExprToBinaryOperation::getOperatorSymbol() const {
    return operatorSymbol;
}

void SyntaxTree::ExprToBinaryOperation::setOperatorSymbol(const std::string &operatorSymbol) {
    ExprToBinaryOperation::operatorSymbol = operatorSymbol;
}

SyntaxTree::Cgen SyntaxTree::ExprToBinaryOperation::cgen() {
    Cgen cgen, op1, op2;
    op1 = operand1->cgen();
    op2 = operand2->cgen();
    cgen.append(op1);
    cgen.append(op2);
    if (operatorSymbol == "==" || operatorSymbol == "!=") {
        // TODO check compatibility
        cgen.createVar("bool", 0);
        cgen.append("Assign " + cgen.var + " = " + op1.var + " " + operatorSymbol + " " + op2.var + "\n");
    } else if (operatorSymbol == "<" ||
               operatorSymbol == "<=" ||
               operatorSymbol == ">" ||
               operatorSymbol == ">=") {
        if (op1.typeName.getId() == op2.typeName.getId() && (op1.typeName.getId() == "int" || op1.typeName.getId() == "double")) {
            cgen.createVar("bool", 0);
            cgen.append("Assign " + cgen.var + " = " + op1.var + " " + operatorSymbol + " " + op2.var + "\n");
        } else
            ; // TODO raise semantic error
    } else if (operatorSymbol == "+" ||
               operatorSymbol == "-" ||
               operatorSymbol == "*" ||
               operatorSymbol == "/" ||
               operatorSymbol == "%") {
        if (op1.typeName.getId() == op2.typeName.getId() && (op1.typeName.getId() == "int" || op1.typeName.getId() == "double")) {
            cgen.createVar("int", 0);
            cgen.append("Assign " + cgen.var + " = " + op1.var + " " + operatorSymbol + " " + op2.var + "\n");
        } else
            ; // TODO raise semantic error
    } else if (operatorSymbol == "||" ||
               operatorSymbol == "&&") {
        if (op2.typeName.getId() == "bool" && op1.typeName.getId() == "bool") {
            cgen.createVar("bool", 0);
            cgen.append("Assign " + cgen.var + " = " + op1.var + " " + operatorSymbol + " " + op2.var + "\n");
        } else
            ; // TODO raise semantic error
    } else
        assert(0); // unknown binary operation
    return cgen;
}

void SyntaxTree::ExprToBinaryOperation::handleScope() {
    operand1->setScope(getScope());
    operand2->setScope(getScope());
    operand1->handleScope();
    operand2->handleScope();
}

const std::string &SyntaxTree::ExprToUnaryOperation::getOperatorSymbol() const {
    return operatorSymbol;
}

void SyntaxTree::ExprToUnaryOperation::setOperatorSymbol(const std::string &operatorSymbol) {
    ExprToUnaryOperation::operatorSymbol = operatorSymbol;
}

SyntaxTree::Expr *SyntaxTree::ExprToUnaryOperation::getOperand() const {
    return operand;
}

void SyntaxTree::ExprToUnaryOperation::setOperand(SyntaxTree::Expr *operand) {
    ExprToUnaryOperation::operand = operand;
}

SyntaxTree::Expr *SyntaxTree::ExprToNewArray::getExpr() const {
    return expr;
}

void SyntaxTree::ExprToNewArray::setExpr(SyntaxTree::Expr *expr) {
    ExprToNewArray::expr = expr;
}

SyntaxTree::Type *SyntaxTree::ExprToNewArray::getType() const {
    return type;
}

void SyntaxTree::ExprToNewArray::setType(SyntaxTree::Type *type) {
    ExprToNewArray::type = type;
}

SyntaxTree::Cgen SyntaxTree::ExprToNewArray::cgen() {
    Cgen cgen;
    Cgen size_cgen = expr->cgen();
    cgen.append(size_cgen);
    cgen.createVar(type->getTypeNameId(), type->getDimension());
    cgen.append("Assign " + cgen.var + " = " + size_cgen.var + " + 1\n");
    cgen.append("Alloc " + cgen.var + " " + cgen.var + "\n");
    cgen.append("Store *(" + cgen.var + ") = " + size_cgen.var + "\n");
    return cgen;
}

void SyntaxTree::ExprToNewArray::handleScope() {
    expr->setScope(getScope());
    expr->handleScope();
    type->setScope(getScope());
    type->handleScope();
}

SyntaxTree::Cgen SyntaxTree::ExprToReadInteger::cgen() {
    Cgen cgen;
    cgen.createVar("int", 0);
    cgen.append("Input " + cgen.var + "\n");
    return cgen;
}

SyntaxTree::Cgen SyntaxTree::ExprToNew::cgen() {
    auto classType = SymbolTable::ClassType::getClass(this->getId());
    int layoutSize = classType->getObjectLayoutSize();
    auto cgen = Cgen();
    cgen.createVar(classType->getId(), 0);
    cgen.append("Alloc " + cgen.var + " " + std::to_string(layoutSize) + "\n");
    return cgen;
}

const std::string &SyntaxTree::ExprToNew::getId() const {
    return Id;
}

void SyntaxTree::ExprToNew::setId(const std::string &id) {
    Id = id;
}

void SyntaxTree::ExprToNew::handleScope() {
    // nothing to do!
}
