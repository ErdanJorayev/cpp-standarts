// В этом файле изучим определение типа возврата через auto

#include <iostream>

// В С++11, типы мы возвращали используя auto с decltype

// C++11: Приходилось явно указывать '-> int' или '-> decltype(...)'
auto add(int a, int b) -> int
{
    return a + b;
}

// C++14: Компилятор сам смотрит на 'a + b' и понимает,
// что возвращается int
auto new_add(int a, int b)
{
    return a + b;
}

// Это работает и с шаблоннами функциями
template <typename T, typename U>
auto temp_add(T a, U b)
{
    return a + b; // Компилятор сам поймет: int + double = double
}

int main()
{
    return 0;
}
