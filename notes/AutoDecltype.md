`auto` в отличие от `decltype` отрезает ссылку и константность 
`decltype` - захватывает ссылки, `auto` - копирует элемент

`decltype(a)` - передаем имя переменной а
`dectype((a))`- передаем выражение в которой есть переменная а (тип выражения - ссылка)
Все эти выражения проверяются на этапе компиляции и заменяются на тип. Самого вычисления выражения  внутри скобок не происходит.

Пример:
```C++
Array<Unit *> units;
	for(size_t i = 0; i != units.size(); ++i) {
		// Unit *
		auto u = units[i];
// Array<Item> const &
decltype(u->items()) items = u->items();
...
auto a = items[0]; // a - Item
decltype(items[0]) b = a; // b - Item const &

decltype(a) c = a; // c - Item
decltype((a)) d = a; // d - Item &

decltype(b) f = b; // f - Item const &
decltype((b)) e = b; // e - Item const &


```