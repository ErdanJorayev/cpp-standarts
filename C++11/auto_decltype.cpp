// В этом файле мы изучим работу auto и decltype

#include <iostream>
#include <vector>

// Если в шаблонную функцию передаем разные типы, можно
// определить возвращаемый тип через auto и decltype
template <typename T, typename U>
auto add(T a, U b) -> decltype(a + b) // decltype можно делать и так
{
    return a + b; // Если T = int, а U = double, вернет double
}

int main()
{
    // auto определяет тип, но сбрасывает ссылки и const
    auto cars = 26;            // По умолчанию тип int
    auto money = 23.3;         // По умолчанию тип double
    auto name = "Alex Mercer"; // По умолчанию тип const char *

    // Тут чтобы убедиться мы выводим размеры типов
    std::cout << "Cars is: " << cars
              << " and size: " << sizeof(cars) << '\n';

    std::cout << "Money is: " << money
              << " and size: " << sizeof(money) << '\n';

    std::cout << "Name is: " << name
              << " and size: " << sizeof(name) << '\n';


    // auto удобен еще и для работы c контейнерами в цикле
    std::vector<int> arr = {55, 66, 77};

    std::cout << "Numbers: ";
    for(const auto & nums : arr)  // Определяем тип без написание
        std::cout << nums << ' '; // длинной строки типа
    std::cout << '\n';

    //decltype возвращает полностью точный тип
    const int x = 42;
    const int & ref = x;
    double y;

    // Тип определяется с учетом других переменных
    decltype(x) a = 55;    // const int
    decltype(ref) b = x;   // const int &

    // Данные можно сначала объявить потом присвоить
    decltype(y) c;
    c = 77;

    std::cout << "a is " << a << '\n';
    std::cout << "b is " << b << '\n';
    std::cout << "c is " << c << '\n';

    // Работаем с шаблонной функцией в связке auto и decltype
    std::cout << "3 + 44.6 = " << add(3, 44.6) << '\n';

    return 0;
}

// Бонус
// Есть такая операция -> с функциями. Ее мы видили в decltype

// СТАРЫЙ СИНТАКСИС (C++98): Выглядит очень запутанно
// int (*getOperatorOld())(int, int) { return add; }

// НОВЫЙ СИНТАКСИС (C++11): Понятно и прозрачно
// Функция getOperator возвращает указатель на функцию `int(*)(int, int)`
auto getOperator() -> int(*)(int, int) {
    return add;
}






