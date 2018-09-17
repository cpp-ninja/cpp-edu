//
// Created by dan on 15.09.18.
//

#include <cstdlib>

struct Expression;
struct Number;
struct BinaryOperation;

struct ScopedPtr
{
    // реализуйте следующие методы:
    //
    //конструктор
    explicit ScopedPtr(Expression *ptr = 0){
        this->ptr_= ptr;
    }
    //деструктор
    ~ScopedPtr(){
        delete ptr_;
        ptr_ = NULL;
    }
    //метод для получения указателя
    Expression* get() const {
        return ptr_;
    }
    //забирает указатель у ScopedPtr и возвращает значение этого указателя, после вызова release ScopedPtr
    // не должен освобождать память (например, чтобы вернуть этот указатель из функции);
    Expression* release(){
        Expression*  rel = ptr_;
        ptr_ = NULL;
        return rel;
    }
    //Метод заставляет ScopedPtr освободить старый указатель, а вместо него захватить новый
    // (например, чтобы переиспользовать ScopedPtr, так как оператор присваивания запрещен).
    void reset(Expression *ptr = 0){
        delete ptr_;
        ptr_ = ptr;

    }
    //оператор разыменования
    Expression& operator*() const {
        return *ptr_;
    }
    // оператор обращения к полю
    Expression* operator->() const {
        return ptr_;
    }


private:
    // запрещаем копирование ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};