// В этом файле изучим Non-Type Template Parameters с auto (C++17)

#include <iostream>

// C++17: auto вместо конкретного типа для шаблонной константы
template <auto Value>
struct Settings
{
    static void show()
    {
        std::cout << "Value: " << Value << '\n';
    }
};

// Сочетание auto NTTP с Fold Expressions (C++17)
template <auto... Values>
void print_all_values()
{
    ((std::cout << Values << ' '), ...);
    std::cout << '\n';
}

int main()
{
    // Тип выводится автоматически из переданного значения:
    Settings<100>::show();      // Value имеет тип int
    Settings<'A'>::show();      // Value имеет тип char
    Settings<true>::show();     // Value имеет тип bool

    // Вариативный список констант разных типов
    print_all_values<1, 'x', false, 42L>();

    return 0;
}
