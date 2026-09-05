// В этом файле изучим работу типа long long в C++11

#include <iostream>

// До С++11 тип long long не входил в официальный стандарт C++ (хотя существовал в C99)
// В C++11 тип long long (и unsigned long long) официально стандартизирован
// Стандарт C++11 гарантирует, что long long занимает НЕ МЕНЕЕ 64 бит (8 байт)

// unsigned int (4 байта) вмещает число до 4 294 967 295.
// unsigned long long (8 байт) вмещает число до 18 446 744 073 709 551 615
int main()
{
    int int_num = 23;
    long long long_long_num = 23;

    // Можно увидеть что long long занимает 8 байта, int 4
    std::cout << "int size: "       << sizeof(int_num) << '\n'
              << "long long size: " << sizeof(long_long_num) << '\n';

    // По умолчанию обычный литерал, число 4 например
    // имеет тип int. Можно с помощью суффиксов LL сделать его long long
    auto inum = 22;    // Обычные числа имеют по умолчнанию тип int
    auto llnum = 22LL; // Мы явно указали что это тип long long

    std::cout << "int size: "       << sizeof(inum) << '\n'
              << "long long size: " << sizeof(llnum) << '\n';

    return 0;
}
