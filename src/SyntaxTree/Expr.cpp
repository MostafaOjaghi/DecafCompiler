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

SyntaxTree::LValue *SyntaxTree::ExprToLValue::getLValue() const {
    return lValue;
}

void SyntaxTree::ExprToLValue::setLValue(SyntaxTree::LValue *lValue) {
    ExprToLValue::lValue = lValue;
}

SyntaxTree::Cgen SyntaxTree::ExprToLValue::cgen() {
    return lValue->cgen();
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
