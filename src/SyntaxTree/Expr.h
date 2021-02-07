//
// Created by Yeganeh Gharedaghi on 2021-01-27.
//

#ifndef DECAFCOMPILER_EXPR_H
#define DECAFCOMPILER_EXPR_H

#include "Node.h"
#include "LValue.h"
#include "Constant.h"
#include "Type.h"

namespace SyntaxTree {
    class Call;

    class Expr : public Node {

    };

    class ExprToAssignmentExpr : public Expr {
    private:
        LValue *lValue;
        Expr *expr;
    public:
        Cgen cgen() override;

        void handleScope() override;

        LValue *getLValue() const;

        void setLValue(LValue *lValue);

        Expr *getExpr() const;

        void setExpr(Expr *expr);
    };

    class ExprToConstant : public Expr {
    private:
        Constant *constant;
    public:
        Cgen cgen() override;

        void handleScope() override;

        Constant *getConstant() const;

        void setConstant(Constant *constant);
    };

    class ExprToLValue : public Expr {
    private:
        LValue *lValue;
    public:
        Cgen cgen() override;

        LValue *getLValue() const;

        void setLValue(LValue *lValue);
    };

    class ExprToThis : public Expr {
    };

    class ExprToCall : public Expr {
    private:
        Call *call;
    public:
        Call *getCall() const;

        void setCall(Call *call);
    };

    class ExprToParenthesisExpr : public Expr {
    private:
        Expr *expr;
    public:
        Cgen cgen() override;

        Expr *getExpr() const;

        void setExpr(Expr *expr);
    };

    class ExprToBinaryOperation : public Expr {
    private:
        std::string operatorSymbol;
        Expr *operand1;
        Expr *operand2;
    public:
        Cgen cgen() override;

        const std::string &getOperatorSymbol() const;

        void setOperatorSymbol(const std::string &operatorSymbol);

        Expr *getOperand1() const;

        void setOperand1(Expr *operand1);

        Expr *getOperand2() const;

        void setOperand2(Expr *operand2);

    };

    class ExprToUnaryOperation : public Expr {
    private:
        std::string operatorSymbol;
        Expr *operand;
    public:
        const std::string &getOperatorSymbol() const;

        void setOperatorSymbol(const std::string &operatorSymbol);

        Expr *getOperand() const;

        void setOperand(Expr *operand);
    };

    class ExprToReadInteger : public Expr {
    public:
        Cgen cgen() override;
    };

    class ExprToReadLine : public Expr {

    };

    class ExprToNew : public Expr {

    };

    class ExprToNewArray : public Expr {
    private:
        Expr *expr;
        Type *type;
    public:
        Expr *getExpr() const;

        void setExpr(Expr *expr);

        Type *getType() const;

        void setType(Type *type);
    };

    class ExprToITOD : public Expr {

    };

    class ExprToDTOI : public Expr {

    };

    class ExprToITOB : public Expr {

    };

    class ExprToBTOI : public Expr {

    };
}

#endif //DECAFCOMPILER_EXPR_H
