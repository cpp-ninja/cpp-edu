
Найти все временные обьекты в реализации функции FindAddr:


```C++
#include <string>
#include <list>

class Employee{
public:
    Employee(std::string name) : name_(name){
        
    }
    std::string addr;
private:
    std::string name_;
  
};

bool operator==(const Employee& lhs, const Employee& rhs){
    return lhs.name_==rhs.name_;
}


std::string FindAddr(std::list<Employee> emps, std::string name){
    for(std::list<Employee>::iterator i = emps.begin();
            i != emps.end(); i++){
        if(*i == name){
            return i->addr;
        }
    }
    return "";
}
```
1. std::list<Employee> emps, std::string name - должны передаваться по константной ссылке.
2. emps.end() - возвращает временный обьект, можно использовать один раз 
3. i++ - постфиксный инкремент запоминает старое значение и возвращает его
4. == name - создание временного обьекта Employee
5. `return i->addr`, `return ""` - возвращение временных строк 

Решение 1:
```c++
std::string FindAddr(const std::list<Employee>& emps, const std::string& name){
    std::list<Employee>::const_iterator end(emps.end());
    for(std::list<Employee>::const_iterator i = emps.begin();
        i != end; ++i){
        if(i->name == name){
            return i->addr;
        }
    }
    return "";
} 
```

Решение 2:
```C++

std::string FindAddr(const std::list<Employee>& emps, const std::string& name){
    std::list<Employee>::const_iterator i(std::find(emps.begin(), emps.end(), name));
    if(i != emps.end()){
        return i->addr;
    }
    return "";
}
```