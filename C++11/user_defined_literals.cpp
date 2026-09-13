// В этом файле изучим работу пользовательских литералов
// (User-defined literals) в C++11

#include <iostream>

// Пользовательский тип для представления тока (Амперы)
class Power
{
private:
    double amperes;

public:
    // Конструктор
    constexpr explicit Power(double amp) : amperes(amp) {}

    // Метод для получения значения
    constexpr double get_amperes() const { return amperes; }
};

// 1. UDL-операторы ДОЛЖНЫ быть глобальными функциями, а не методами класса
// 2. Обязателен символ '_' в начале суффикса
// 3. Для чисел с плавающей точкой аргумент строго 'long double'
constexpr Power operator"" _A(long double amp)
{
    return Power(static_cast<double>(amp));
}

// Перегрузка для целых чисел (сигнатура строго с unsigned long long)
// Можно и с базовыми типами
constexpr unsigned long long operator"" _A(unsigned long long amp)
{
    return amp;
}

int main()
{
    // Теперь это работает и создает объект Power напрямую из числа
    Power am1 = 23.5_A;
    unsigned long long am2 = 10_A;

    std::cout << "Power 1: " << am1.get_amperes() << " A\n";
    std::cout << "Power 2: " << am2 << " A\n";

    return 0;
}
