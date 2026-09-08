// В этом файле изучим работу using в С++11

#include <iostream>
#include <string>
#include <map>

// По сути using это замена старому typedef
// Главное отличие в удобстве читаемости
// и с работой шаблнонами

// Старый стиль
typedef unsigned long long ull;

// Новый
using Ull = unsigned long long;

// Особенно читаемость заметна при работе с указателями на функции
typedef int (*old_func_ptr)(int, double);

using new_func_ptr = int (*)(int, double);

// В С++11 можно создавать псевдонимы который сам принимает
// шаблонный параметр

// Старый стиль, по сути костыль через структурную обертку
template <typename T>
struct oldstringmap
{
    typedef std::map<std::string, T> type;
};

// Новый стиль
template <typename T>
using newstringmap = std::map<std::string, T>;

int main()
{
    oldstringmap<int>::type my_oldmap; // Неудобно

    newstringmap<double> prices;       // Выглядит удобнее

    return 0;
}
