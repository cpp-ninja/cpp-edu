Напишите код, удаляющй все значения равные трем из `std::vector<int>`
Напишите код удаления n-ого элемента .
Решение:
1)Частное решение

```c++
std::vector<int> v = {1,2,3,4,3,2,1};
v.erase(remove(v.begin(), v.end(), 3), v.end());
```	
`remove()` физически не удалет элементы, а перемещает их в конец вектора. `erase()`- избавляется от всех "мертвых" элементов.

2) Обобщенное решение удаления n-ого элемента:
```c++
template< typename FwdIter>
FwdIter remove_nth(FwdIter first, FwdIter last, size_t n){
    assert(distance(first, last ) >= n);

    advance(first, n);
    if(first != last){
        FwdIter dest = first;
        return copy(++first, last, dest);
    }
    return last;
}
```
`copy()` - возвращает оutput-итератор на элемент в целевом диапазоне, следующий сразу за последним скопированным элементом. 

2) Решение с помощью предиката

```c++
class FlagNth{
public:
    FlagNth(size_t size): current_(0), n_(size){}
    template <typename  T>
    bool operator()(const T& t){ return ++current_==n_; }
private:
    size_t       current_;
    const size_t n_;
};

remove_if(v.begin(), v.end(), FlagNth(3));
```

