// В этом файле изучим работу alignof и alignas в С++11.

#include <iostream>

// Естественное выравнивание:
// Порядок полей неоптимален (char -> padding -> int -> double),
// поэтому alignof(Simp) равен выравниванию самого строгого поля (double)
struct Simp
{
    char c;   // 1 байт
    int i;    // 4 байта
    double d; // 8 байт
};

// Оптимизированная вручную структура (сортировка полей от большего к меньшему):
// Уменьшаем расход памяти за счет сжатия невидимых отступов (padding)
struct GoodSimp
{
    double d; // 8 байт
    int i;    // 4 байта
    char c;   // 1 байт
};

// Плохой порядок: char разбросаны вокруг double (много дыр в памяти)
struct BadLayout
{
    char c1;   // 1 байт (+ 7 байт padding)
    double d;  // 8 байт
    char c2;   // 1 байт (+ 7 байт padding)
}; // sizeof = 24 байта

// Хороший порядок: группируем одинаковые и мелкие типы
struct GoodLayout
{
    double d;  // 8 байт
    char c1;   // 1 байт
    char c2;   // 1 байт (+ 6 байт padding в конце)
}; // sizeof = 16 байт



// Принудительное выравнивание под кэш-линию процессора (64 байта):
// Используется для SIMD-инструкций или предотвращения False Sharing в многопоточности
struct alignas(64) Fire
{
    int ball; // 4 байта полезных данных + 60 байт отступа (padding)!
};

int main()
{
    std::cout << "Оператор alignof (Запрос выравнивания)\n";
    std::cout << "alignof(char):     " << alignof(char) << '\n';   // 1
    std::cout << "alignof(int):      " << alignof(int) << '\n';    // 4
    std::cout << "alignof(double):   " << alignof(double) << '\n'; // 8
    std::cout << "alignof(Simp):     " << alignof(Simp) << '\n';   // 8 (по double)

    std::cout << "Сравнение размеров из-за Padding\n";
    std::cout << "sizeof(Simp):      " << sizeof(Simp) << " bytes\n";     // 16 байт (из-за дыр в памяти)
    std::cout << "sizeof(GoodSimp):  " << sizeof(GoodSimp) << " bytes\n"; // 16 байт (но отступ в конце меньше)

    std::cout << "Спецификатор alignas(N)\n";
    // alignas форсирует адрес и раздувает sizeof всей структуры до кратности N!
    std::cout << "alignof(Fire):     " << alignof(Fire) << '\n';   // 64
    std::cout << "sizeof(Fire):      " << sizeof(Fire) << " bytes (4 bytes data + 60 bytes padding)\n"; // 64

    std::cout << "sizeof(BadLayout):  " << sizeof(BadLayout) << " bytes\n";  // 24
std::cout << "sizeof(GoodLayout): " << sizeof(GoodLayout) << " bytes\n"; // 16 (экономия 8 байт!)

    return 0;
}
