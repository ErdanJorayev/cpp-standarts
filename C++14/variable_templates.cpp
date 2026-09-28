// В этом файле изучим работу variable templates в С++14

#include <type_traits>

// До С++14, шаблонами можно было делать только функции, структуры/классы
// Начиная с С++14, шаблонами можно делать и переменные

// Суть шаблонности, мы определяем тип переменной
// Например есть какая-то константа, число пи например
// Для одной ситуации она требуется как float, для другой как double
// или вообще как long double

// Раньше чтобы такое делать создавали шаблонные функции или класс обертки
// Теперь, в С++14 можно явно делать переменную шаблонной
template <typename T>
constexpr T pi = T(3.1415926535897932);

// До C++14 проверяли свойства типов так: std::is_integral<T>::value
// В C++14/17 благодаря variable templates появились удобные _v синонимы
template <typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;

int main()
{
    float f = pi<float>;
    double d = pi<double>;
    // То есть тип константы выбираем вручную

    // Задействуем нашу шаблонную переменную is_integral_v
    bool check_int = is_integral_v<int>; // true

    // Обрати внимание: встроенные _v (например, std::is_same_v)
    // появились в стандарте C++17, поэтому для C++14 создаем свой алиас:
    bool is_same_type = std::is_same<int, double>::value; // false

    return 0;
}
