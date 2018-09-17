
Ключевое слово inline советует компилятору встроить данную функцию.

`inline double square ( double x ) { return x * x ; }`

∙ В месте вызова inline-функции должно быть известно её
определение.

∙ inline функции можно определять в заголовочных
файлах.

∙ Все методы, определённые внутри класса, являются
inline.

∙ При линковке из всех версий inline-функции (т.е. её код
из разных единиц трансляции) выбирается только одна.

∙ Все определения одной и той же inline-функции должны
быть идентичными.

∙ inline — это совет компилятору, а не указ.