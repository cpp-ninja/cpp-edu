 Задача 2.1

 Создать класс ci_string, нечувствительный к регистру символов.

 Решение :

```c++

#include <cassert>
#include <cstring>
#include <string>
#include <bits/char_traits.h>  // NB: In turn includes stl_algobase.h


struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char c1, char c2) { return toupper(c1) == toupper(c2); }
    static bool ne(char c1, char c2) { return toupper(c1) != toupper(c2); }
    static bool lt(char c1, char c2) { return toupper(c1) <  toupper(c2); }
    static int compare(const char* s1, const char* s2, size_t n) {
        while( n-- != 0 ) {
            if( toupper(*s1) < toupper(*s2) ) return -1;
            if( toupper(*s1) > toupper(*s2) ) return 1;
            ++s1; ++s2;
        }
        return 0;
    }
    static const char* find(const char* s, int n, char a) {
        while( n-- > 0 && toupper(*s) != toupper(a) ) {
            ++s;
        }
        return s;
    }
};
typedef std::basic_string<char, ci_char_traits> ci_string;
int main(){
    ci_string str = "LoL";
    assert(strcmp(str.c_str(), "LoL") ==0);
    assert(strcmp(str.c_str(), "lol") !=0 );
    assert(str == "Lol");
    assert(str == "lol");
}
``` 
