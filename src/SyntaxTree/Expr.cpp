//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#include "Expr.h"
#include "Type.h"

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

SyntaxTree::Cgen SyntaxTree::ExprToAssignmentExpr::cgen() {
    Cgen cgen;
    Cgen lvalue_cgen = lValue->cgen();
    Cgen expr_cgen = expr->cgen();
    cgen.code += expr_cgen.code;
    cgen.code += lvalue_cgen.code;
    cgen.code += "Assign " + lvalue_cgen.var + " = " + expr_cgen.var + "\n";
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
    return lValue->cgen();
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

SyntaxTree::Expr *SyntaxTree::ExprToParenthesisExpr::getExpr() const {
    return expr;
}

void SyntaxTree::ExprToParenthesisExpr::setExpr(SyntaxTree::Expr *expr) {
    ExprToParenthesisExpr::expr = expr;
}

SyntaxTree::Cgen SyntaxTree::ExprToParenthesisExpr::cgen() {
    return expr->cgen();
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
    cgen.code += op1.code + op2.code;
    cgen.var = UniqueGenerator::newTemp();
    cgen.code += "Assign " + cgen.var + " = " + op1.var + " " + operatorSymbol + " " + op2.var + "\n";
    cgen.var_count = op1.var_count + op2.var_count + 1;
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

SyntaxTree::Cgen SyntaxTree::ExprToReadInteger::cgen() {
    Cgen cgen;
    cgen.var = UniqueGenerator::newTemp();
    cgen.code = "Input " + cgen.var + "\n";
    cgen.var_count = 1;
    return cgen;
}
