// В этом файле изучим работу variadic using - declarations

#include <iostream>
#include <string>

// ОБЫЧНЫЙ СПИСОК ИМЁН ЧЕРЕЗ ЗАПЯТУЮ
struct BaseA
{
    void foo(int x) { std::cout << "BaseA::foo(" << x << ")\n"; }
};

struct BaseB
{
    void bar(double y) { std::cout << "BaseB::bar(" << y << ")\n"; }
};

struct Derived : BaseA, BaseB
{
    // C++17: Внедряем имена из обоих базовых классов в ОДНОЙ строчке!
    using BaseA::foo, BaseB::bar;
};

// ВАРИАТИВНЫЙ USING ДЛЯ ЛЯМБД И ПАТТЕРНА OVERLOADED
template <typename... Ts>
struct Overloader : Ts... {
    // C++17: Раскрытие пакета параметров в using-объявлении!
    using Ts::operator()...;
};

// CTAD гид для Overloader (тоже C++17)
template <typename... Ts>
Overloader(Ts...) -> Overloader<Ts...>;


int main()
{
    // Простая интеграция имён
    Derived d;
    d.foo(42);
    d.bar(3.14);

    // Объединение нескольких лямбд в один объект перегрузок!
    auto match = Overloader
    {
        [](int x) { std::cout << "Int matched: " << x << '\n'; },
        [](const std::string& s) { std::cout << "String matched: " << s << '\n'; },
        [](double d) { std::cout << "Double matched: " << d << '\n'; }
    };

    match(100);             // Вызовет лямбду (int)
    match("Hello C++17");   // Вызовет лямбду (string)
    match(3.1415);          // Вызовет лямбду (double)

    return 0;
}
