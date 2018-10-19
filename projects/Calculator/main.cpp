#include <iostream>
#include "calculator.h"

const char * quit = "exit()";

void help(){
    std::cout << "Calculator 1.0" << std::endl;
    std:: cout <<"Use: (r|f|c|b) expression" <<std::endl;
}

void calc(std::ostream & out, std::istream & in){
    help();


    std::string input;
    Calculator calculator;
    out<<"> ";
    while(getline(in, input)){
        if(input == quit){
            exit(1);
        }
        try {
            size_t found = input.find(' ');
            if (found == 1) {
                char mode = input[0];
                Type type;
                switch (mode){
                    case 'r':{
                        type = Type::REAL;
                        break;
                    }case 'f':{
                        type = Type ::FRACTION;
                        break;
                    }case 'c':{
                        type = Type::COMPLEX;
                        break;
                    }case 'b':{
                        type = Type::BINARY;
                        break;
                    }
                    default:{
                        throw std::invalid_argument("wrong type");
                    }
                }

                out << "= " << calculator.evaluate(type, input.substr(1)) <<std::endl;
                out << "> ";
            } else {
                throw std::invalid_argument("wrong format");
            }
        } catch (const std::exception & exception){
            out << "Error: " << exception.what() << std::endl;
            out << "> ";
            continue;
        }
    }
}

int main() {
    calc(std::cout, std::cin);
    return 0;
}