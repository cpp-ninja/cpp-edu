//
// Created by cpp-ninja on 05.10.18.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H


#include <string>
#include <ostream>
#include "numbers.h"
#include <memory>
#include <stack>
#include <sstream>
#include <vector>
#include <complex>

enum class Type {
    REAL, COMPLEX, FRACTION, BINARY
};

class Calculator {
public:
    Calculator() = default;

    std::string evaluate(Type type, const std::string &expression);


    template <typename NumType>
    std::shared_ptr<Number> eval(const std::string& expr){
        auto rpn = make_rpn_nodes<NumType>(expr);
        return eval_rpn<NumType>(rpn);
    }


    template <typename NumType>
    std::pair<NumType , NumType > getOperandsFromStack(std::stack<NumType>& stack){
        if(stack.size() < 2) throw std::invalid_argument("wrong expression");
        NumType left = stack.top();
        stack.pop();
        NumType right = stack.top();
        stack.pop();
        return std::make_pair(left, right);
    }

    template <typename NumType>
    NumType perfomOperation(char operation, const NumType& lhs, const NumType& rhs){
        switch (operation){
            case '+' : {
                return lhs + rhs;
            }
            case '-' : {
                return rhs - lhs;
            }
            case '*' : {
                return rhs * lhs;
            }
            case '/' : {
                return rhs / lhs;
            }
            case '^' : {
                return rhs ^ lhs;
            }
        }
    }

    BinaryNumber perfomBinaryOperation(char operation, const Number* left, const Number* right){
        BinaryNumber lhs = *(dynamic_cast<const BinaryNumber *>(left));
        BinaryNumber rhs = *(dynamic_cast<const BinaryNumber *>(right));

        switch (operation){
            case '+' : {
                return  lhs + rhs;
            }
            case '-' : {
                return rhs - lhs;
            }
            case '*' : {
                return rhs * lhs;
            }
            case '/' : {
                return rhs / lhs;
            }
            case '^' : {
                return rhs ^ lhs;
            }
            case '|':{
                return lhs | rhs;
            }
            case '&': {
                return lhs & rhs;
            }
        }
    }

    template<typename NumType>
    std::shared_ptr<NumType> eval_rpn(std::deque<std::shared_ptr<Node>>& nodes){
        std::stack<NumType> results;
        while (!nodes.empty()){
            Node* node = nodes.front().get();
            switch (node->type_){
                case 'o':{
                    Operation* operation = dynamic_cast<Operation*>(node);
                    auto operands = getOperandsFromStack(results);
                    NumType result;
                    if(!isBinary) result = perfomOperation(operation->op_, operands.first, operands.second);
                    else {
                        BinaryNumber num = perfomBinaryOperation(operation->op_,
                                                                 dynamic_cast<Number *>(&operands.first),
                                                                 dynamic_cast<Number *>(&operands.second));
                        result = *(dynamic_cast<NumType*>(dynamic_cast<Number *>(&num)));
                    }
                    results.push(result);
                    break;
                }
                case 'r':
                case 'c' :
                case 'f':
                case 'b' :{
                    auto number = *(dynamic_cast<NumType*>(node));
                    results.push(number);
                    break;
                }
            }
            nodes.pop_front();
        }
        return std::make_shared<NumType>(results.top());
    }
    template<typename NumType>
    std::deque<std::shared_ptr<Node>> make_rpn_nodes(const std::string &expression) {
        std::stringstream in(expression);
        std::deque<std::shared_ptr<Node>> rpn;
        std::stack<char> stack;
        char ch;
        while (in >> ch) {
            switch (ch) {
                case '+':case '-':case '*' :case '/':
                case '^': case '&': case '|': {
                    if(!stack.empty()) {
                        while (get_priority(ch) < get_priority(stack.top()) ||
                               ((is_left_operation(stack.top())) && (get_priority(ch) == get_priority(stack.top())))) {
                            //if (stack.empty()) break;
                            char op = stack.top();
                            stack.pop();
                            rpn.push_back(std::make_shared<Operation>(op));
                            if (stack.empty()) break;
                        }
                    }
                    stack.push(ch);
                    break;
                }
                case '(': {
                    stack.push(ch);
                    break;
                }
                case ')' : {
                    char op = stack.top();
                    while (op != '(') {
                        if (stack.empty()) {
                            throw std::invalid_argument("wrong expression( missing parenthesis)");
                        }
                        op = stack.top();
                        stack.pop();
                        rpn.push_back(std::make_shared<Operation>(op));
                        op = stack.top();
                    }
                    stack.pop();
                    break;
                }
                case '0': case '1':case '2':case '3':case '4':
                case '5':case '6':case '7':case '8': case '9': {
                    in.putback(ch);
                    NumType num;
                    in >> num;
                    rpn.push_back(std::make_shared<NumType>(num));
                    break;
                }
                case ' ': {
                    break;
                }
                default:{
                    throw std::invalid_argument("extra symbols");
                }
            }

        }
        while (!stack.empty()) {
            char op = stack.top();
            stack.pop();
            rpn.push_back(std::make_shared<Operation>(op));
        }

        return rpn;
    }

    int get_priority(char op);

    static bool is_left_operation(char op);




private:
    bool isBinary = false; // flag for get_priority

};




#endif //CALCULATOR_CALCULATOR_H
