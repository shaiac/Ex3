//
// Created by shaiac on 20/12/2019.
//

#include "Expression.h"
#include "ex1.h"
#include <stack>
#include <queue>
#include <string>

Value::Value(double v) { this->value = v; }

double Value::GetValue() { return this->value; }

double Value::calculate() { return this->GetValue(); }

Variable::Variable(string na, double val) {
    this->value = val;
    this->name = na;
}

string Variable::GetName() {
    return this->name;
}

double Variable::calculate() { return this->value; }

void Variable::SetValue(double num) {
    this->value = num;
}

Variable &Variable::operator++() {
    ++(this->value);
}

Variable &Variable::operator--() {
    --(this->value);
}

Variable &Variable::operator++(int) {
    (this->value)++;
}

Variable &Variable::operator--(int) {
    (this->value)--;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
}

Variable &Variable::operator-=(double num) {
    this->value -= num;
}

UnaryOperator::UnaryOperator(Expression *exp) {
    this->expression = exp;
}

UnaryOperator::~UnaryOperator() {
    delete (expression);
}

Expression *UnaryOperator::GetExp() {
    return this->expression;
}

UPlus::UPlus(Expression *exp) : UnaryOperator(exp) {}

double UPlus::calculate() {
    return this->GetExp()->calculate();
}

UMinus::UMinus(Expression *exp) : UnaryOperator(exp) {}

double UMinus::calculate() {
    return this->GetExp()->calculate() * -1;
}

BinaryOperator::BinaryOperator(Expression *l, Expression *r) {
    this->right = r;
    this->left = l;
}

BinaryOperator::~BinaryOperator() {
    delete (right);
    delete (left);
}

Expression *BinaryOperator::GetLeft() {
    return this->left;
}

Expression *BinaryOperator::GetRight() {
    return this->right;
}

Plus::Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {}

double Plus::calculate() {
    return (this->right->calculate() + this->left->calculate());
}

Minus::Minus(Expression *l, Expression *r) : BinaryOperator(l, r) {}

double Minus::calculate() {
    return (this->left->calculate() - this->right->calculate());
}

Mul::Mul(Expression *l, Expression *r) : BinaryOperator(l, r) {}

double Mul::calculate() {
    return (this->right->calculate() * this->left->calculate());
}

Div::Div(Expression *l, Expression *r) : BinaryOperator(l, r) {}

double Div::calculate() {
    double rightNum = this->right->calculate();
    if (rightNum == 0) {
        throw "bad input";
    }
    return (this->left->calculate() / rightNum);
}
/**
 *
 * @param varibsInString equation of varribale
 * take the string and add the varriable to the interpreter
 */
void Interpreter::setVariables(string varibsInString) {
    for (int i = 0; i < varibsInString.length(); i++) {
        string name = "";
        string num = "";
        while (!(varibsInString[i] == '=')) {
            name += varibsInString[i];
            i++;
        }
        if (name[name.length() - 1] == ' ') {
            name = name.substr(0, name.length() - 1);
        }
        i++;
        while (!(varibsInString[i] == ';') && i < varibsInString.length()) {
            num += varibsInString[i];
            i++;
        }
        try {
            double value = stod(num);
            if (!this->DidThereVar(name, value)) {
                Variable var = {name, value};
                this->varbs.push_back(var);
            }
        }
        catch (exception e) {
            throw "bad input";
        }
    }

}

queue <string> Interpreter::IntoPostfix(string expInString) {
    stack<char> stack;
    queue <string> postf;
    int i = 0;
    int flagForOpen = 0;
    int max = expInString.length();
    while (i < max) {
        if (expInString[i] > 47 && expInString[i] < 58) {
            string num = "";
            while ((expInString[i] > 47 && expInString[i] < 58) || (expInString[i] == '.' && !num.empty())) {
                num += expInString[i];
                i++;
            }
            if (expInString[i] == '.') {
                i++;
            }
            postf.push(num);
            continue;
        }

        if ((expInString[i] > 64 && expInString[i] < 91) || (expInString[i] > 96 && expInString[i] < 123)) {
            string varName = "";
            while ((expInString[i] > 64 && expInString[i] < 91) || (expInString[i] > 96 && expInString[i] < 123) ||
                   (expInString[i] > 47 && expInString[i] < 58) || (expInString[i] == '_')) {
                varName += expInString[i];
                i++;
            }
            postf.push(varName);
            continue;
        }

        if (expInString[i] == '(') {
            flagForOpen++;
            stack.push(expInString[i]);
            i++;
            if (expInString[i] == '+') {
                stack.push('$');
                i++;
            }
            if (expInString[i] == '-') {
                stack.push('#');
                i++;
            }
            if (expInString[i] == '*' || expInString[i] == '/') {
                throw "bad input";
            }
            continue;
        }
        if (expInString[i] == '+' || expInString[i] == '-') {
            int upper = 1;
            if (expInString[i + 1] == '*' || expInString[i + 1] == '/' || expInString[i + 1] == '+'
                || expInString[i + 1] == '-') {
                throw "bad input";
            }
            if (!stack.empty() && !(stack.top() == '(') && !(stack.top() == '$') && !(stack.top() == '#')) {
                AddingOper(&stack, &postf, false);
            }
            if (stack.empty() && postf.empty()) {
                if (expInString[i] == '+') {
                    stack.push('$');
                }
                if (expInString[i] == '-') {
                    stack.push('#');
                }
            } else {
                stack.push(expInString[i]);
            }
            i += upper;
            continue;
        }
        if (expInString[i] == '*' || expInString[i] == '/') {
            if (expInString[i + 1] == '*' || expInString[i + 1] == '/') {
                throw "bad input";
            }
            int upper = 1;
            if (expInString[i + 1] == '+' || expInString[i + 1] == '-') { //check if we got unary exp after
                if (expInString[i + 1] == '+') {
                    stack.push('$');
                }
                if (expInString[i + 1] == '-') {
                    stack.push('#');
                }
                upper++; //skip the char we already pushed
            }
            if (!stack.empty() && !stack.top() == '(' && !stack.top() == '+' && !stack.top() == '-' &&
                !(stack.top() == '$')) {
                AddingOper(&stack, &postf, false);
            }
            stack.push(expInString[i]);
            i += upper;
            continue;
        }
        if (expInString[i] == ')') {
            if (flagForOpen <= 0 || stack.empty()) {
                throw "bad input";
            }
            flagForOpen--;
            this->AddingOper(&stack, &postf, true);
            i++;
            continue;
        }
        if (expInString[i] == ' ') {
            i++;
            continue;
        }
        throw "bad input"; // after we checked all the available chars
    }
    AddingOper(&stack, &postf, false);
    if (flagForOpen != 0) {
        throw "bad input";
    }
    return postf;

}

void Interpreter::AddingOper(stack<char> *stack, queue <string> *queue, bool rightParen) {
    while (!stack->empty()) {
        char c = stack->top();
        if (c == '(') { //break when the () finished or until the end
            stack->pop();
            break;
        }
        string str1 = "";
        str1 += c;
        queue->push(str1);
        stack->pop();
    }

}

double Interpreter::GetValueOfVarriable(string str) {
    list <Variable> vars;
    int flag = 0;
    vars.operator=(this->varbs);
    while (!vars.empty()) {
        Variable check = vars.front();
        if (check.GetName() == str) {
            flag++;
            return (check.calculate());
        }
        vars.pop_front();
    }
    if (flag == 0) {
        throw "bad input";
    }
}

/**
 *
 * @param str
 * @param num
 * @return if the var was exist and the func chnged his value, or not exist at all
 */
bool Interpreter::DidThereVar(string str, double num) {
    list <Variable> vars;
    bool flag = false;
    while (!this->varbs.empty()) {
        Variable check = this->varbs.front();
        if (check.GetName() == str) {
            Variable newOne = {str, num};
            vars.push_back(newOne);
            flag = true;
        } else {
            vars.push_back(check);
        }
        this->varbs.pop_front();
    }
    while (!vars.empty()) {
        this->varbs.push_back(vars.front());
        vars.pop_front();
    }
    return flag;
}

BinaryOperator *Interpreter::CharToBinary(char oper, Expression *left, Expression *right) {
    if (oper == '+') {
        return new Plus(left, right);
    }
    if (oper == '-') {
        return new Minus(left, right);
    }
    if (oper == '*') {
        return new Mul(left, right);
    }
    if (oper == '/') {
        return new Div(left, right);
    }
}

UnaryOperator *Interpreter::CharToUnary(char oper, Expression *expression) {
    if (oper == '$') {
        return new UPlus(expression);
    }
    if (oper == '#') {
        return new UMinus(expression);
    }
}


Expression *Interpreter::interpret(string expInString) {
    queue <string> postf;
    postf = this->IntoPostfix(expInString);
    stack < Expression * > stack;
    while (!postf.empty()) {
        string expAsString = postf.front();
        int c = expAsString[0];
        if (c > 47 && c < 58) {
            try {
                double num = stod(expAsString);
                Value *v = new Value(num);
                stack.push(v);
            }
            catch (exception e) {
                throw "bad input";
            }
        }
        if ((c > 64 && c < 91) || (c > 96 && c < 123)) {
            double num = this->GetValueOfVarriable(expAsString);
            Value *v = new Value(num);
            stack.push(v);
        }
        if (expAsString[0] == '+' || expAsString[0] == '-' || expAsString[0] == '*' || expAsString[0] == '/') {
            Expression *right = stack.top();
            stack.pop();
            Expression *left = stack.top();
            stack.pop();
            Expression *buildUp = this->CharToBinary(expAsString[0], left, right);
            stack.push(buildUp);
        }
        if (expAsString[0] == '$' || expAsString[0] == '#') {
            Expression *expression = stack.top();
            stack.pop();
            Expression *buildUp = this->CharToUnary(expAsString[0], expression);
            stack.push(buildUp);
        }
        postf.pop();
    }
    return stack.top();
}