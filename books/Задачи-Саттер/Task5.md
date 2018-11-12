Напишите программу ECHO  которая просто повторяет вводимую информацию 

`ECHO infile outfiile` - вводимую информацию берет из infile и записывает в outfile.

Решение  :

```c++
#include <iostream>
#include <fstream>
#include <bits/char_traits.h>  

//Полиморфизм времени компиляции
template <typename Out, typename In>
void Process( In&& in, Out&& out){
   out << in.rdbuf();
}
/// Более гибкое решение
template <typename C = char, typename T = std::char_traits<C>>
void Process(std::basic_istream<C, T>&& in, std::basic_ostream<C, T>&& out){
    out <<in.rdbuf();
};

int main(int argc, char ** argv){
    using namespace std;

    fstream in , out;
    if (argc > 1) in.open(argv[1], ios::in | ios::binary);
    if (argc > 2) out.open(argv[2], ios::out | ios::binary);

    Process( in.is_open() ? in : cin,
             out.is_open()? out : cout );
    return 0;
}
```
