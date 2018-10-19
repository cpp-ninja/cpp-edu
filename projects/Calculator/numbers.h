//
// Created by cpp-ninja on 05.10.18.
//

#ifndef CALCULATOR_NUMBERS_H
#define CALCULATOR_NUMBERS_H

#include <string>
#include <bitset>
#include <iostream>
#include <complex>

const int BITS_NUM = 16;
const int DOUBLE_PRECISION = 2;

class Node {
public:
    explicit Node(char type) : type_(type){}
    char type_;
    virtual ~Node() = default;

};

class Operation : public  Node {
public:
    explicit Operation(char op) : Node('o') , op_(op){}
    char op_;
};

class Number : public Node {
public:
    Number() : Node('n'){ }

    explicit Number(char ch) :Node(ch) {}
    virtual std::string toString() const ;
    ~Number() = default;
    Number operator +(const Number& right);
};


class ComplexNumber : public Number{
public:


    ComplexNumber(const ComplexNumber &number);

    friend class Calculator;

    ComplexNumber(double real, double imag);
    ComplexNumber();


    std::string toString() const override ;

    std::complex<double> &getComplex(){
        return complex_;
    }
    std::complex<double> complex() const{
        return complex_;
    }

private:
    std::complex<double> complex_;
};

ComplexNumber operator +(const ComplexNumber& left, const ComplexNumber& right);
ComplexNumber operator -(const ComplexNumber& left, const ComplexNumber& right);
ComplexNumber operator /(const ComplexNumber& left, const ComplexNumber& right);
ComplexNumber operator *(const ComplexNumber& left, const ComplexNumber& right);
ComplexNumber operator ^(const ComplexNumber& left, const ComplexNumber& right);

std::istream &operator>>(std::istream &in, ComplexNumber &number);

class FractionNumber : public Number {
public:
    FractionNumber() {
        numerator_=0;
        denominator_=1;
    }
    std::string toString() const override ;

    FractionNumber(int numerator, int denominator);

    int Numerator() const {
        if (isNegative){
            return -numerator_;
        }
        return numerator_;
    }

    int Denominator() const {
        return denominator_;
    }
    int nod(int a, int b) ;

private:
    int numerator_;
    int denominator_;
    bool isNegative = false;
};

bool operator ==(const FractionNumber& r1,const FractionNumber& r2);

FractionNumber operator +(const FractionNumber& r1, const FractionNumber& r2);

FractionNumber operator -(const FractionNumber& r1, const FractionNumber& r2);

FractionNumber operator *(const FractionNumber& r1, const FractionNumber& r2);

FractionNumber operator /(const FractionNumber& r1, const FractionNumber& r2);

FractionNumber operator^(const FractionNumber &lhs,const FractionNumber &rhs );

bool operator < (const FractionNumber& lhs, const FractionNumber& rhs);



class RealNumber : public Number{

    friend  std::istream& operator >> (std::istream& in, RealNumber& number);

public:
    RealNumber() : Number('r'), value_(0) {}
    explicit RealNumber(double value);
    std::string toString() const override ;


    double getValue() const {
        return value_;
    }

private:
    double value_;
};

RealNumber operator + (const RealNumber&left, const RealNumber& right);
RealNumber operator - (const RealNumber&left, const RealNumber& right);
RealNumber operator * (const RealNumber&left, const RealNumber& right);
RealNumber operator / (const RealNumber&left, const RealNumber& right);
RealNumber operator ^ (const RealNumber&left, const RealNumber& right);


bool operator ==(const RealNumber&left, const RealNumber& right);


class BinaryNumber : public Number{
public:

    explicit BinaryNumber(const std::string &bits);
    BinaryNumber();
    explicit BinaryNumber(const char *bits);

    BinaryNumber&operator =(const BinaryNumber& number);
    BinaryNumber(const BinaryNumber& number);
    explicit BinaryNumber(ulong num);

    std::string toString() const override ;

    std::bitset<BITS_NUM> bits() const {
        return *bits_;
    }

    ~BinaryNumber() override ;
private:

    std::bitset<BITS_NUM>* bits_;
};

BinaryNumber operator +(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator -(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator *(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator /(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator ^(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator &(const BinaryNumber& left, const BinaryNumber& right);
BinaryNumber operator |(const BinaryNumber& left, const BinaryNumber& right);

std::ostream& operator << (std::ostream& os, const FractionNumber& rational);

std::istream& operator >> (std::istream& is, FractionNumber& rational);

std::istream& operator >> (std::istream& in, BinaryNumber& number);

std::istream& operator >> (std::istream& in, RealNumber& number);

std::ostream& operator << (std::ostream& out, const Number &number );

#endif //CALCULATOR_NUMBERS_H
