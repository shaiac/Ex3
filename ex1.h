//
// Created by omer on 8.11.2019.
//
using namespace std;

#include <string>
#include "Expression.h"
#include <queue>
#include <stack>
#include <list>

#ifndef EX1_EX1_H

class Value : public Expression {

private:
    double value;

public:
    Value(double v);

    double GetValue();

    double calculate();


};

class Variable : public Expression {

private:
    string name;

    double value;

public:
    Variable(string na, double val);

    string GetName();

    void SetValue(double num);

    Variable &operator++(); //++x
    Variable &operator--(); //--x
    Variable &operator+=(double);

    Variable &operator-=(double);

    Variable &operator++(int);

    Variable &operator--(int);

    double calculate();


};

class UnaryOperator : public Expression {
private:
    Expression *expression;

public:
    UnaryOperator(Expression *exp);

    Expression *GetExp();

    ~UnaryOperator();

};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression *exp);

    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression *exp);

    double calculate();
};

class BinaryOperator : public Expression {

protected:
    Expression *left;

    Expression *right;

public:
    BinaryOperator(Expression *l, Expression *r);

    Expression *GetLeft();

    Expression *GetRight();

    ~BinaryOperator();

};

class Plus : public BinaryOperator {
public:
    Plus(Expression *l, Expression *r);

    double calculate();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression *l, Expression *r);

    double calculate();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression *l, Expression *r);

    double calculate();
};

class Div : public BinaryOperator {
public:
    Div(Expression *l, Expression *r);

    double calculate();
};

class Interpreter {
private:
    list<Variable> varbs;
public:
    queue<string> IntoPostfix(string expInString);

    void setVariables(string varibsInString);

    Expression *interpret(string expInString);

    void AddingOper(stack<char> *stack, queue<string> *queue, bool rightParen);

    double GetValueOfVarriable(string str);

    BinaryOperator *CharToBinary(char oper, Expression *left, Expression *right);

    UnaryOperator *CharToUnary(char oper, Expression *expression);

    bool DidThereVar(string str, double num);

};


#define EX1_EX1_H

#endif //EX1_EX1_H
