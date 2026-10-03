// В этом файле изучим работу this в лямбдах в С++17

#include <iostream>
#include <functional>

// До С++17, можно было передавать только this в лямбду
// Проблема была в том что объект которому принадлежит this,
// может быть уничтожен до использование отдельной лямбды которая
// захватила объект через this

// Решением стал синтаксис *this. То есть мы передаем целый объект
// в лямбду, а лямбда как мы помним скрытно создает класс.
// В этом классе будет своя копия объект которого передали через *this

struct DataPrinter
{
    int data = 100;

    // Опасно для асинхронного кода (C++11)
    auto get_unsafe_lambda()
    {
        return [this]() { return data; }; // Хранит только адрес this
    }

    // Безопасно для асинхронного кода (C++17)
    auto get_safe_lambda()
    {
        return [*this]() { return data; }; // Копирует весь объект *this
    }
};

int main()
{
    std::function<int()> unsafe_fn;
    std::function<int()> safe_fn;

    {
        DataPrinter printer;
        unsafe_fn = printer.get_unsafe_lambda();
        safe_fn   = printer.get_safe_lambda();
    } // printer уничтожился здесь

    // unsafe_fn(); // Опасность! UB (dangling pointer)
    std::cout << "Safe result: " << safe_fn() << '\n'; // ОК: выведет 100

    return 0;
}
