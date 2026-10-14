// В этом файле изучим работу lambda init capture в С++14


#include <iostream>
#include <memory>
#include <string>
#include <utility>

// Вспомогательная функция для демонстрации
std::string get_prefix() 
{
    return "[LOG]";
}

int main() 
{
    std::cout << "=== Lambda Init Capture (C++14) ===\n";

    // ------------------------------------------------------------------------
    // 1. Захват с перемещением (Move-only types)
    // ------------------------------------------------------------------------
    auto ptr = std::make_unique<int>(42);

    // До C++14 это вызвало бы ошибку компиляции (unique_ptr нельзя скопировать)
    // В C++14 объявляем 'p' внутри лямбды и перемещаем в него 'ptr'
    auto print_ptr = [p = std::move(ptr)]() 
    {
        std::cout << "Value inside unique_ptr: " << *p << '\n';
    };

    // 'ptr' теперь равен nullptr, владение полностью перешло к лямбде
    if (!ptr) 
        std::cout << "Original ptr is now nullptr.\n";

    print_ptr();

    // ------------------------------------------------------------------------
    // 2. Создание абсолютно новых переменных внутри лямбды
    // ------------------------------------------------------------------------
    // Переменные 'tag' и 'counter' не существуют во внешнем контексте
    auto logger = [tag = get_prefix(), counter = 1]() mutable 
    {
        std::cout << tag << " Message #" << counter++ << '\n';
    };

    logger(); // [LOG] Message #1
    logger(); // [LOG] Message #2

    // ------------------------------------------------------------------------
    // 3. Оптимизация: Захват результатов вычислений
    // ------------------------------------------------------------------------
    int base_val = 10;
    // Вычисляем сложную инициализацию один раз при создании лямбды, а не при каждом её вызове
    auto precalculated_task = [factor = base_val * 42 + 7]() 
    {
        std::cout << "Precalculated factor: " << factor << '\n';
    };

    precalculated_task();

    return 0;
}