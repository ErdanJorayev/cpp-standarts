// В этом файле изучаем Aggregate Initialization with Default Member Initializers (C++14)

#include <iostream>
#include <string>

// Агрегат — это простая структура без пользовательских конструкторов.
// В C++11 добавление '= value' к полю запрещало использовать агрегатную
// инициализацию через фигурные скобки {}.

// В C++14 это исправили: теперь структура остается агрегатом,
// даже если у полей есть значения по умолчанию.

struct Profile
{
    std::string role = "Guest";
    int level = 1;
};

int main()
{
    // В C++14 это работает идеально:
    Profile p1{"Admin", 80}; // Переопределили оба поля
    Profile p2{"Moderator"}; // role = "Moderator", level = 1 (взялся по умолчанию)
    Profile p3{};            // role = "Guest", level = 1

    std::cout << p2.role << " level: " << p2.level << '\n';

    return 0;
}
