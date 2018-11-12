Какие требования к алгоритму следует предъявлять, чтобы обеспечить корректную работу предикатов с состоянием?

1) Алгоритм не должен делать копий предиката
2)Алгоритм должен применять предикат в некотором определенном порядке( например от первого элемента до последнего)

Предикат с состоянием который можно безопасно использовать в алгоритмах:

```C++
template <typename T>
class CountedPtr {
private:
    class Impl{
    public:
        explicit Impl(T* pp) : p(pp), refs(1){}
        ~Impl(){delete p ;}
        T*     p;
        size_t refs;
    };
    Impl* impl_;
public:
    explicit CountedPtr(T* p) :  impl_(new Impl(p)){}
    ~CountedPtr(){Decrement();}
    CountedPtr(CountedPtr& other) : impl_(other.impl_){
        Increment();
    }
    CountedPtr& operator = (const CountedPtr& other){
        if(impl_ != other.impl_){
            Decrement();
            impl_ = other.impl_;
            Increment();
        }
        return *this;
    }
    T* operator ->() const {
        return impl_->p;
    }
    T& operator*(){
        return *(impl_->p);
    }

private:
    void Decrement(){
        if(--(impl_->refs) == 0){
            delete impl_;
        }
    }
    void Increment(){
        ++(impl_->refs);
    }
};

class FlagNthImpl{
public:
    explicit FlagNthImpl(size_t nn) : i(0), n(nn){}
    size_t       i;
    const size_t n;
};

class FlagNth{
public:
    FlagNth(size_t n) :pimpl_(new FlagNthImpl(n)) {}

    template <typename T>
    bool operator ()(const T&){
        return ++(pimpl_->i) == pimpl_->n;
    }

private :
    CountedPtr<FlagNthImpl> pimpl_;
};
``` 