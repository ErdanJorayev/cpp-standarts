// В этом файле изучим Class Template Argument Deduction / CTAD (C++17)

#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
#include <string>

int main()
{
    // Раньше (До C++17):
    // std::tuple<int, int, double> t_old(4, 3, 2.5);
    // auto t_old2 = std::make_tuple(4, 3, 2.5);

    //C++17 (CTAD): Компилятор сам выводит типы из аргументов конструктора
    std::tuple t(4, 3, 2.5); // Тип: std::tuple<int, int, double>
    std::pair p(100, "C++17"); // Тип: std::pair<int, const char*>
    std::vector v = {1, 2, 3, 4}; // Тип: std::vector<int>

    // Доступ к элементам кортежа (сочетается со Structured Bindings из C++17!)
    auto [a, b, c] = t;
    std::cout << "Tuple elements: " << a << ", " << b << ", " << c << '\n';

    return 0;
}
