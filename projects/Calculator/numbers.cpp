//
// Created by cpp-ninja on 05.10.18.
//

#include <sstream>
#include <iomanip>
#include <cmath>
#include "numbers.h"

/*                         Number                                   */
std::string Number::toString() const {
    return "lol";
}

Number Number::operator+(const Number &right) {
    return Number();
}


std::ostream &operator<<(std::ostream &out, const Number &number) {
    out  << number.toString();
    return out ;
}



/*                     ComplexNumber                                    */


ComplexNumber::ComplexNumber(double real, double imag) : Number('c'), complex_(real, imag) {}

std::string ComplexNumber::toString() const {
    char sign = (complex().imag() >= 0) ?'+': '-';
    std::stringstream ss;
    ss << complex().real();
    ss <<" " <<sign << " ";
    ss << complex().imag() <<"i";
    return ss.str();
}


ComplexNumber::ComplexNumber(const ComplexNumber &number)
        : Number('c'), complex_(number.complex_.real(), number.complex_.imag()) {

}
ComplexNumber operator^(const ComplexNumber& left, const ComplexNumber &right) {
    throw std::domain_error("Operation ^ for complex not implemented");
}

ComplexNumber operator+(const ComplexNumber& left, const ComplexNumber &right) {
    auto sum = left.complex() + right.complex();
    return ComplexNumber(sum.real(), sum.imag());
}

ComplexNumber operator-(const ComplexNumber& left, const ComplexNumber &right) {
    auto sub = left.complex() - right.complex();
    return ComplexNumber(sub.real(), sub.imag());
}

ComplexNumber operator*(const ComplexNumber& left, const ComplexNumber &right) {
    auto mul = left.complex() * right.complex();
    return ComplexNumber(mul.real(), mul.imag());
}

ComplexNumber operator/(const ComplexNumber& left, const ComplexNumber &right) {
    auto div = left.complex() / right.complex();
    return ComplexNumber(div.real(), div.imag());
}

ComplexNumber::ComplexNumber() :Number('c'), complex_(0, 0){}

std::istream &operator>>(std::istream &in, ComplexNumber &number) {
    int imag, real;
    char sign, let;
    in >> real;
    in >> sign;
    in >> imag;
    if(sign != '+' && sign != '-'){
        throw std::domain_error("Wrong complex number");
    }
    in >> let;
    if(let != 'i' && let != 'j'){
        throw std::domain_error("Wrong complex number");
    }
    number.getComplex().imag(imag);
    number.getComplex().real(real);
    return in;

}



/*                     FractionNumber                                   */


FractionNumber::FractionNumber(int numerator, int denominator)
        : Number('f'), numerator_(numerator), denominator_(denominator) {
    if(denominator==0){
        throw std::invalid_argument("zero denominator");
    }

    if( numerator <0 || denominator <0){
        numerator = abs(numerator);
        denominator = abs(denominator);
        isNegative = true;
    }
    if(numerator ==0){
        denominator = 1;

    }
    int n = nod(numerator, denominator);
    if(n!=-1) {
        numerator_ = numerator / n;
        denominator_ = denominator / n;
    }else{
        numerator_ = numerator;
        denominator_= denominator;
    }
}


int FractionNumber::nod(int a, int b) {

    if (b > a) {
        int temp = a;
        a = b;
        b = temp;
    } else if (b == a) {
        return b;
    }
    if (b != 0) {
        if (a % b == 0) {
            return b;
        }
    }else return -1;

    while(a!=b){
        if(a>b){
            int temp = a;
            a =b;
            b = temp;
        }
        b= b -a;
        if(b<0){
            break;
        }
    }
    return a;
}


std::istream &operator>>(std::istream &is, FractionNumber &rational) {
    std::string string1;
    is >>string1;
    if(!string1.empty()) {
        std::stringstream stringstream1(string1);
        int p = 0;
        int q =1;
        stringstream1 >> p;
        stringstream1.ignore(1);
        stringstream1 >> q;
        rational = FractionNumber(p,q);
    }
    return is;
}


FractionNumber operator-(const FractionNumber &r1, const FractionNumber &r2) {
    int temp_p = r1.Numerator()*r2.Denominator() - r2.Numerator()* r1.Denominator();
    int temp_q = r2.Denominator()*r1.Denominator();
    return FractionNumber(temp_p, temp_q);
}


FractionNumber operator+(const FractionNumber &r1, const FractionNumber &r2) {
    int temp_p = r1.Numerator()*r2.Denominator() +r2.Numerator()* r1.Denominator();
    int temp_q = r2.Denominator()*r1.Denominator();
    return FractionNumber(temp_p, temp_q);
}


FractionNumber operator^(const FractionNumber &lhs,const FractionNumber &rhs ){
    int temp_p = static_cast<int>(pow(lhs.Numerator(), rhs.Numerator() / rhs.Denominator()));
    int temp_q = static_cast<int>(pow(lhs.Denominator(), rhs.Numerator() / rhs.Denominator()));
    return FractionNumber(temp_p, temp_q);
}


bool operator==(const FractionNumber &r1, const FractionNumber &r2) {
    return r1.Denominator() == r2.Denominator() && r1.Numerator() == r2.Numerator();
}


std::ostream &operator<<(std::ostream &os, const FractionNumber &rational) {
    os << rational.Numerator()<<"/"<<rational.Denominator();
    return os;
}


bool operator<(const FractionNumber &lhs, const FractionNumber &rhs) {
    if(lhs.Denominator()==rhs.Denominator()){
        return lhs.Numerator() < rhs.Numerator();
    }else return ((lhs - rhs).Numerator() < 0);
}


FractionNumber operator*(const FractionNumber &r1, const FractionNumber &r2) {
    return {r1.Numerator()* r2.Numerator(), r1.Denominator()* r2.Denominator()};
}


FractionNumber operator/(const FractionNumber &r1, const FractionNumber &r2) {
    if(r2.Numerator()!=0) {
        return FractionNumber(r1.Numerator() * r2.Denominator(), r2.Numerator() * r1.Denominator());
    }else{
        throw std::domain_error(" division by zero");
    }
}


std::string FractionNumber::toString() const {
    std::stringstream ss;
    ss << numerator_ << "/" <<denominator_;
    return ss.str();
}




/*                             RealNumber                         */

RealNumber::RealNumber(double value) : Number('r'), value_(value) {}

std::string RealNumber::toString() const {
    std::stringstream ss;
    ss << std::setprecision(DOUBLE_PRECISION);
    ss <<std::fixed << getValue();
    return ss.str();
}

std::istream &operator>>(std::istream &in, RealNumber &number) {
    in >> number.value_;
    return in;
}

RealNumber  operator+(const RealNumber& left, const RealNumber &right) {
    return RealNumber( left.getValue() + right.getValue());
}

RealNumber operator*(const RealNumber& left, const RealNumber &right) {
    return RealNumber(left.getValue()* right.getValue());
}

RealNumber  operator-(const RealNumber& left, const RealNumber &right) {
    return RealNumber(left.getValue() - right.getValue());
}

RealNumber operator /(const RealNumber& left, const RealNumber &right) {
    if(right.getValue() == 0 ) throw std::invalid_argument("division by zero");
    return RealNumber(left.getValue() / right.getValue());
}

RealNumber operator^(const RealNumber& left, const RealNumber &right) {
    return RealNumber(pow(left.getValue(), right.getValue()));
}

bool operator ==(const RealNumber &left, const RealNumber &right) {
    return left.getValue() == right.getValue();
}


/*                             BinaryNumber                                    */




BinaryNumber::BinaryNumber(const std::string& bits) : Number('b'){
    bits_ = new std::bitset<BITS_NUM>(bits);
}

BinaryNumber::BinaryNumber(const char * bits) :Number('b') {
    bits_ = new std::bitset<BITS_NUM>(bits);
}

std::string BinaryNumber::toString() const {
    return bits_->to_string();
}

BinaryNumber::~BinaryNumber() {
    //std::cout << "delete bits: " +bits_->to_string() << std::endl;
    delete(bits_);
}

BinaryNumber::BinaryNumber() : Number('b'), bits_(new std::bitset<16>("0")){}


BinaryNumber::BinaryNumber(ulong num) :Number('b') {
    this->bits_ = new std::bitset<BITS_NUM>(num);
}

BinaryNumber::BinaryNumber(const BinaryNumber &number) : Number('b'){
    if(number.bits_ == nullptr){
        std::cout << "Error"<<std::endl;
    }
    //std::cout <<"copy constructor from bits: " +number.bits_->to_string() << std::endl;
    this->bits_= new std::bitset<BITS_NUM>(*number.bits_);
}

BinaryNumber &BinaryNumber::operator=(const BinaryNumber &number) {
    if(this != &number){
        for (size_t i = 0; i < BITS_NUM ; ++i) {
            this->bits_->set(i, number.bits_->test(i));
        }
    }
    return *this;
}

BinaryNumber operator+(const BinaryNumber& left, const BinaryNumber &right) {
    auto  sum = left.bits().to_ulong() + right.bits().to_ulong();
    return BinaryNumber(sum);
}

BinaryNumber operator-(const BinaryNumber& left, const BinaryNumber &right) {
    auto diff = left.bits().to_ulong() - right.bits().to_ulong();
    return BinaryNumber(diff);
}

BinaryNumber operator*(const BinaryNumber& left, const BinaryNumber &right) {
    auto mul = left.bits().to_ulong() * right.bits().to_ulong();
    return BinaryNumber(mul);
}

BinaryNumber operator/(const BinaryNumber& left, const BinaryNumber &right) {
    auto div =left.bits().to_ulong() / right.bits().to_ulong();
    return BinaryNumber(div);
}

BinaryNumber operator^(const BinaryNumber& left, const BinaryNumber &right) {
    return BinaryNumber(((left.bits() ) ^ (right.bits())).to_string());
}

BinaryNumber operator&(const BinaryNumber& left, const BinaryNumber &right) {
    return BinaryNumber(((left.bits()) & (right.bits())).to_string());
}

BinaryNumber operator|(const BinaryNumber& left, const BinaryNumber &right) {
    return BinaryNumber(((left.bits() ) | (right.bits())).to_string());
}



std::istream &operator>>(std::istream &in, BinaryNumber &number) {
    std::string num;
    in >> num;
    number = BinaryNumber(num);
    return in;
}



