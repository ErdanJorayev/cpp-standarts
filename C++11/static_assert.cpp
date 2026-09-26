// В этом файле изучим работу static_assert в C++11

#include <iostream>
#include <type_traits> // Для проверки типа

// static_assert помогает проверить какое-либо условие во время компиляции
// То есть условие ложное, программа не скомпилируется, будет ошибка
// Первый аргумент оператора само выражение, второе сообщение об ошибке

template <typename T>
T add(T a, T b)
{
    // Разрешаем вызывать функцию только для арифметических типов (int, float и т.д.)
    static_assert(std::is_arithmetic<T>::value, "add() works only with arithmetic types!");
    return a + b;
}

int main()
{
    add(23, 44);          // Типы int
    // add("abc", "cba"); // Типы const char *, ошибка компиляции

    // Или просто обычный пример
    //static_assert(2 > 3, "2 > 3 is fail"); // Будет ошибка компиляции

    return 0;
}
