// В этом файле изучим работу Generalized PODs в C++11

#include <iostream>
#include <type_traits> // Обязательно для работы std::is_pod, std::is_trivial и std::is_standard_layout

// В C++11 понятие POD (Plain Old Data) разделено на два независимых критерия:
// 1. Trivial types (тривиальные типы) — можно копировать через memcpy.
// 2. Standard-layout types (типы со стандартным размещением) — совместимы с C-ABI по представлению в памяти.
// Если тип одновременно Trivial и Standard-layout, он является POD-типом в C++11.

// По своей сути Generalized POD означает, что объект хранит ТОЛЬКО сырые данные.
// То есть там не создается каких-то скрытых данных в памяти (вроде vptr на таблицу виртуальных функций)
// и не выполняются какие-либо скрытые операции при создании/удалении.
// Поэтому с ним можно безопасно работать через memcpy, скопировав чисто данные, которые лежат подряд.

// Данные public, конструкторы по умолчанию, нет ничего лишнего
struct GenPod
{
    int age;
    char ch;
};

int main()
{
    // Проверка во время компиляции (Compile-time)
    static_assert(std::is_pod<GenPod>::value, "GenPod must be a valid POD type!");

    // Вывод результатов проверки в рантайме
    std::cout << std::boolalpha; // Вывод true и false вместо 1 и 0
    std::cout << "GenPod is_pod: " << std::is_pod<GenPod>::value << '\n';
    std::cout << "GenPod is_trivial: " << std::is_trivial<GenPod>::value << '\n';
    std::cout << "GenPod is_standard_layout: " << std::is_standard_layout<GenPod>::value << '\n';

    return 0;
}
