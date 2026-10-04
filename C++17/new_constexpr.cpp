// В этом файле изучим обновление constexpr в С++17

#include <iostream>
#include <type_traits>
#include <string>

// До С++17, constexpr проверял обе ветки if на этапе компиляции
// Возникала проблема когда одна из веток содержала недопустимый код
// В С++17, ветка которая false, полностью отбрасывается компилятором
template <typename T>
auto get_value(T t)
{
    if constexpr (std::is_pointer_v<T>)
    {
        return *t;  // Разыменовываем, ЕСЛИ T — указатель
    }
    else
    {
        return t;   // Возвращаем как есть, ЕСЛИ T — не указатель
    }
}

// Также добавили использовать лямбды в constexpr выражениях
int main()
{
    int val = 42;
    int * ptr = &val;

    std::cout << get_value(val) << '\n'; // Компилируется! Ветка с *t отброшена для int
    std::cout << get_value(ptr) << '\n'; // Компилируется! Ветка без *t отброшена для int*

    // constexpr лямбды, выполнение алгоритмов на этапе компиляции
    constexpr auto add = [](int a, int b) { return a + b; };

    // Проверка прямо во время сборки!
    static_assert(add(10, 20) == 30, "Compile-time addition failed");

    return 0;
}
