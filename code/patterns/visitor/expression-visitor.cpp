//
// Created by dan on 13.09.18.
//

#include <iostream>

using namespace std;

struct Number;
struct BinaryOperation;
struct Visitor;
struct Expression;

struct Visitor {
    virtual void visitNumber(Number const * number) = 0;
    virtual void visitBinaryOperation(BinaryOperation const * binary) = 0;
    virtual ~Visitor() { }
};

struct Expression
{
    virtual double evaluate() const = 0;
    virtual ~Expression(){}
    virtual void visit(Visitor * visitor) const  = 0;
};

struct Number : Expression
{

    double get_value() const { return value; }

    Number(double value)
            : value(value)
    {}
    double evaluate() const {
        return value;
    }

    void visit(Visitor * visitor) const { visitor->visitNumber(this); }
private:
    double value;
};

struct BinaryOperation : Expression
{
    /*
      Здесь op это один из 4 символов: '+', '-', '*' или '/', соответствующих операциям,
      которые вам нужно реализовать.
     */
    BinaryOperation(Expression const * left, char op, Expression const * right)
            : left(left), op(op), right(right)
    { }

    void visit(Visitor * visitor) const {
        visitor->visitBinaryOperation(this);
    }

    double evaluate() const {
        double res = 0.0;
        switch(op){
            case '+': {
                res = left->evaluate() + right->evaluate();
                break;
            }
            case '-': {
                res = left->evaluate() - right->evaluate();
                break;
            }
            case '/': {
                res = left->evaluate() / right->evaluate();
                break;
            }
            case '*': {
                res = left->evaluate() * right->evaluate();
                break;
            }
            default: return 0.0;
        }
        delete left;
        delete right;
        return res;
    }

    Expression const * get_left()  const { return left; }
    Expression const * get_right() const { return right; }
    char get_op() const { return op; }

private:
    Expression const * left;
    Expression const * right;
    char op;
};

struct PrintBinaryOperationsVisitor : Visitor {
    void visitNumber(Number const * number)
    {
        //number->visit(this);
        std::cout << number ->get_value();

    }

    void visitBinaryOperation(BinaryOperation const * bop)
    {
        std::cout<<"(";
        bop->get_left()->visit(this);
        std::cout << bop->get_op() << " ";
        bop->get_right()->visit(this);
        std::cout <<")";
    }
};




int main(){
    // сначала создаём объекты для подвыражения 4.5 * 5
    Expression * sube = new BinaryOperation(new Number(4.5), '*', new Number(5));
// потом используем его в выражении для +
    Expression * expr = new BinaryOperation(new Number(3), '+', sube);

// вычисляем и выводим результат: 25.5
   // std::cout << expr->evaluate() << std::endl;

// тут освобождаются *все* выделенные объекты
// (например, sube будет правым операндом expr, поэтому его удалять не нужно)

    PrintBinaryOperationsVisitor visitor;
    expr->visit(&visitor);
    return 0;
}