#include <iostream>
#include <assert.h>

/*
 * Задание повышенной сложности. 
 * Реализуйте класс SharedPtr как описано ранее. 
 * Задание немного сложнее, чем кажется на первый взгляд. 
 * Уделите особое внимание "граничным случаям" - нулевой указатель, 
 * присваивание самому себе, вызов reset на нулевом SharedPtr и прочее. 
 * Hint: возможно, вам понадобится завести вспомогательную структуру.
 * */

struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
    virtual ~Expression() { }
    virtual double evaluate() const = 0;
};
struct Number : Expression
{
    Number(double value)
        : value_(value)
    {}

    double value() const
    { return value_; }

    double evaluate() const
    { return value_; }

private:
    double value_;
};

struct SharedPtr
{
    // реализуйте следующие методы
    //
    // explicit SharedPtr(Expression *ptr = 0)
    // ~SharedPtr()
    // SharedPtr(const SharedPtr &)
    // SharedPtr& operator=(const SharedPtr &)
    // Expression* get() const
    // void reset(Expression *ptr = 0)
    // Expression& operator*() const
    // Expression* operator->() const

    explicit SharedPtr(Expression *ptr = 0){
        ptr_ = ptr;
        if (ptr_) {
            counter_ = new int(1);
        } else {
            counter_ = 0;
        }
    }
    SharedPtr(const SharedPtr & obj) {
//        if (this != &obj) {
            ptr_ = obj.get(); // копируем указатель
            counter_ = obj.get_counter(); // копируем счетчик 
            if (ptr_){
                ++(*counter_); // увеличиваем счетчие если укзатель не нулевой
            }
//      }
    }

    void reset(Expression *ptr = 0){
        if (ptr_ != ptr){
            decrement_counter();
            ptr_ = ptr;
            if (ptr) {
                counter_ = new int(0);
                if (ptr_) {
                    ++(*counter_);
                }
            }
        }
    }
    SharedPtr& operator=(const SharedPtr & obj) {
        if (this != &obj){
            decrement_counter();
            ptr_ = obj.get();
            counter_ = obj.get_counter();
            if (obj.ptr_) {
                ++(*counter_);
            }
        }
        return *this;
    }
    Expression& operator*() const {
        return *ptr_;
    }
    Expression* operator->() const {
        return ptr_;
    }
    Expression* get() const {
        return ptr_;
    }
    int* get_counter() const{
        if (counter_) return counter_;
        return 0;
    }
    ~SharedPtr(){
        decrement_counter();
    }
    void decrement_counter(){
        if (counter_ && ptr_  && !--(*counter_)) {
            delete ptr_;
            delete counter_;
            counter_ = 0;
        }
    }
    

private:
    Expression *ptr_;
    int *counter_;
};