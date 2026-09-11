// В этом файле продолжим изучение variadic templates,
// если в прошлом файле делали упор на шаблонные
// функции, в этом будет упор на класс

#include <iostream>
#include <string>

// Для шаблонных функций при variadic templates,
// мы создали отдельную остановучную функцию и
// делали рекурсию

// Для класса шаблона это будет работать немного
// по-другому
// Будем делать пример на основе std::tuple

// 1. Объявляем шаблонный класс
template <typename... Args>
class Tuple;

// 2. Как и с шаблонной функцией, нужен
// базовый случай рекурсии, в нашем случае
// пустой кортеж без аргументов
template <>
class Tuple<> {};

// 3. Рекурсивная специализация
// Как и с шаблонной функцией отделяем первый
// тип от остальных
template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : public Tuple<Tail...>
{
public:
    Head data; // Храним первый элемент

    // Конструктор, принимает первый элемент и пакет элементов для базового класса
    Tuple(Head head, Tail... tail)
        : Tuple<Tail...>(tail...), data(head) {}
};

int main()
{
    Tuple<int, double, std::string> cort(42, 3.14, "Hii");

    // 1. Доступ к первому элементу (int) напрямую
    std::cout << "1st element: " << cort.data << '\n'; // 42

    // 2. Доступ ко второму элементу (double):
    // Приводим тип к базовому классу Tuple<double, std::string>
    std::cout << "2nd element: "
              << static_cast<Tuple<double, std::string>&>(cort).data << '\n'; // 3.14

    // 3. Доступ к третьему элементу (std::string):
    // Приводим тип к базовому классу Tuple<std::string>
    std::cout << "3rd element: "
              << static_cast<Tuple<std::string>&>(cort).data << '\n'; // Hii

    return 0;
}
