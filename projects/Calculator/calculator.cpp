//
// Created by cpp-ninja on 05.10.18.
//

#include <memory>
#include <iostream>
#include <sstream>
#include <stack>
#include "calculator.h"

std::string Calculator::evaluate(Type type, const std::string &expression) {

    std::shared_ptr<Number> result;
    switch (type){
        case Type::COMPLEX : {
            result = eval<ComplexNumber>(expression);
            break;
        }
        case Type::FRACTION :{
            result = eval<FractionNumber>(expression);
            break;
        }
        case Type ::BINARY:{
            isBinary = true;
            result = eval<BinaryNumber>(expression);
            isBinary = false;
            break;
        }
        case Type::REAL :{
            result = eval<RealNumber>(expression);
            break;
        }
    }

    std::string answer = result->toString();

    return  answer;
}




int Calculator::get_priority(char op) {
    if(!isBinary){
        switch(op) {
            case '+' :case '-':
                return 1;
            case '*' :case '/' :
                return 2;
            case '^' :
                return 3;
            case ')': case '(':
                return 0;
        }
    }
    else {
        switch(op) {
            case '*' :case '/' :
                return 5;
            case '+' :case '-':
                return 4;
            case '&':
                return 3;
            case '^' :
                return 2;
            case '|':
                return 1;
            case ')': case '(':
                return 0;
        }
    }
}

bool Calculator::is_left_operation(char op) {
    switch(op) {
        case '+': case '*' :
        case '/': case '-': case '^':
            return true;
    }
    return false;
}



