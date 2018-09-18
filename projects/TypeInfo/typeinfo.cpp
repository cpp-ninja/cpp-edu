#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>
#include <iomanip>
#include <climits>
#include <algorithm>
#include <limits>



/*
 *  Sorry for that shit-code. I don't know how to make it shorter and more simple.
 */

using namespace std;

enum TYPE{
    INT, UINT, SHORT, USHORT, LONG, ULONG, LLONG, ULLONG, FLOAT, DOUBLE, LDOUBLE
};

TYPE checkIntType(long long num){

    if (num<= INT16_MAX && num >= INT16_MIN){
        return SHORT;
    }
    if (num <= USHRT_MAX && num >=0){
        return USHORT;
    }
    if(num <=INT32_MAX && num >= INT32_MIN ){
        return INT;
    }
    if(num <=UINT32_MAX && num >= 0 ){
        return UINT;
    }
    if(num <= LONG_MAX && num >= LONG_MIN ){
        return LONG;
    }
    if(num <=ULONG_MAX && num >= 0 ){
        return ULONG;
    }
    if(num <=LLONG_MAX && num >= LLONG_MIN ){
        return LLONG;
    }
    if(num <=ULLONG_MAX && num >= 0 ){
        return ULLONG;
    }
}

TYPE checkRealType(long double num){
    if(num <= numeric_limits<float>::max() && num >= numeric_limits<float>::min() ){
        return FLOAT;
    }
    if(num <= numeric_limits<double>::max() && num >= numeric_limits<double>::min() ){
        return DOUBLE;
    }
    if(num <= numeric_limits<long double>::max() && num >= numeric_limits< long double>::min() ){
        return LDOUBLE;
    }
}

template <typename T>
void printInfo(string name){
    cout << "Name: " << name << endl;
    cout << "Size: " << sizeof(T) <<" bytes" << endl;
    cout << "From: " << numeric_limits<T>::min() << " to "<<  numeric_limits<T>::max() << endl;
}

void printTypeInfo(TYPE type) {

    string name;

    switch (type) {
        case INT: {
            name = "int (signed, signed int)";
            printInfo<int>(name);
            break;
        }
        case UINT:{
            name = "unsigned int( unsigned )";
            printInfo<unsigned>(name);
            break;
        }
        case SHORT:{
            name = "short (short int, signed short int)";
            printInfo<short>(name);
            break;
        }
        case USHORT:{
            name = "unsigned short (unsigned short int)";
            printInfo<unsigned short>(name);
            break;
        }
        case LONG:{
            name = "long (signed long int, long int)";
            printInfo<long>(name);
            break;
        }
        case ULONG: {
            name = "unsigned long (unsigned long int)";
            printInfo<unsigned long>(name);
            break;
        }
        case LLONG: {
            name = "long long (long long int, signed long long int)";
            printInfo<long long >(name);
            break;
        }
        case ULLONG: {
            name = "unsigned long long (unsigned long long int)";
            printInfo<unsigned long long>(name);
            break;
        }
        case FLOAT: {
            name = "float";
            printInfo<float>(name);
            break;
        }
        case DOUBLE:{
            name = "double";
            printInfo<double>(name);
            break;
        }
        case LDOUBLE:{
            name = "long double";
            printInfo<long double>(name);
            break;
        }
        default:{
            throw invalid_argument("not realised");
        }
    }
}

bool isIntNumber(const std::string& s)
{
    return std::find_if(s.begin(), s.end(),[](char c) { return !std::isdigit(c); }) == s.end();
}

bool isRealNumber(const std::string& s)
{
    char* p;
    strtod(s.c_str(), &p);
    return *p == 0;
}

int main() {
    cout << " TypeInfo 1.0 " << endl;
    cout <<"Enter any value " << endl;

    string input;

    cin >> input;

    stringstream in;

    if (!input.empty()){
        in.str(input);
    } else{
        throw runtime_error("Empty string");
    }

    if (isIntNumber(input)){
        long long int i = 0;
        in >> i;
        TYPE type = checkIntType(i);
        printTypeInfo(type);
    } else  if(isRealNumber(input)){
        long double d = 0.0;
        in >> d;
        TYPE type = checkRealType(d);
        printTypeInfo(type);
    }else {
        throw runtime_error("Is not number");
    }


    return 0;
}
