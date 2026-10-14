// ============================================================================
// СТАНДАРТНЫЕ АТРИБУТЫ C++17: [[fallthrough]], [[maybe_unused]], [[nodiscard]]
// ============================================================================

#include <iostream>
#include <cassert>

// 1. [[nodiscard]] на типе: любой возвращаемый ErrorCode нельзя игнорировать
struct [[nodiscard]] ErrorCode {
    int code;
};

ErrorCode perform_setup() {
    return ErrorCode{0};
}

// 2. [[nodiscard]] на функции
[[nodiscard]] int calculate_important_hash(int input) {
    return input * 2654435761;
}

// 3. [[maybe_unused]] на параметрах функции
void process_data(int data, [[maybe_unused]] int flags) {
    [[maybe_unused]] int debug_check = data * 2;
    assert(debug_check > 0); // Не вызовет warning в Release

    std::cout << "Data processed: " << data << '\n';
}

int main()
{
    // --- Демонстрация [[fallthrough]] ---
    int option = 1;
    switch (option) 
    {
        case 1:
            std::cout << "Option 1 initialized.\n";
            [[fallthrough]]; // Явно говорим компилятору: «проваливаемся» в case 2

        case 2:
            std::cout << "Option 1 & 2 shared processing.\n";
            break;
    }

    // --- Демонстрация [[maybe_unused]] ---
    process_data(42, 0);

    // --- Демонстрация [[nodiscard]] ---
    // Если раскомментировать строчки ниже, компилятор выдаст предупреждение/ошибку:
    // perform_setup();
    // calculate_important_hash(100);

    // Правильное использование:
    ErrorCode err = perform_setup();
    int hash = calculate_important_hash(100);

    // Заглушка, если действительно нужно проигнорировать nodiscard
    (void)err;
    (void)hash;

    return 0;
}
