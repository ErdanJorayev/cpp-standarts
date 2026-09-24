// В этом файле изучаем работу noexcept спецификатора и оператора в С++11.

#include <iostream>
#include <utility>   // Для std::move
#include <vector>

// Спецификатор noexcept
// Означает, что функция гарантированно не выбрасывает исключения.
// Оптимизация: компилятор не генерирует таблицы раскрутки стека (Stack Unwinding)
// для этой функции, что уменьшает размер бинарника и ускоряет вызов.

void safe_fun() noexcept
{
    // throw 23; // если раскомментировать, сразу вызовется std::terminate()!
}

void unsafe_fun()
{
    throw std::runtime_error("Error!");
}

// Использование noexcept для Move-семантики
// Это критически важно для контейнеров, таких как std::vector.

struct ElementWithNoexcept
{
    ElementWithNoexcept() = default;

    // Перемещающий конструктор с noexcept
    ElementWithNoexcept(ElementWithNoexcept&&) noexcept
    {
        std::cout << "ElementWithNoexcept: Move constructed\n";
    }

    // Копирующий конструктор
    ElementWithNoexcept(const ElementWithNoexcept&)
    {
        std::cout << "ElementWithNoexcept: Copy constructed\n";
    }
};

struct ElementWithoutNoexcept
{
    ElementWithoutNoexcept() = default;

    // Перемещающий конструктор БЕЗ noexcept
    ElementWithoutNoexcept(ElementWithoutNoexcept&&)
    {
        std::cout << "ElementWithoutNoexcept: Move constructed\n";
    }

    ElementWithoutNoexcept(const ElementWithoutNoexcept&)
    {
        std::cout << "ElementWithoutNoexcept: Copy constructed\n";
    }
};




int main()
{
    std::cout << "=== Оператор noexcept (Compile-time проверка) ===\n";

    int a = 5;
    // Оператор noexcept() возвращает bool во время компиляции
    std::cout << "noexcept(1 + 2): " << noexcept(1 + 2) << '\n';         // 1 (true)
    std::cout << "noexcept(safe_fun()): " << noexcept(safe_fun()) << '\n'; // 1 (true)
    std::cout << "noexcept(unsafe_fun()): " << noexcept(unsafe_fun()) << '\n'; // 0 (false)

    std::cout << "\n--- Vector с noexcept Element ---\n";
    std::vector<ElementWithNoexcept> vec1;
    vec1.reserve(1);
    vec1.emplace_back();
    // При перевыделении памяти vector безопасно использует MOVE, так как есть noexcept:
    vec1.reserve(2);

    std::cout << "\n--- Vector БЕЗ noexcept Element ---\n";
    std::vector<ElementWithoutNoexcept> vec2;
    vec2.reserve(1);
    vec2.emplace_back();
    // Из-за отсутствия noexcept vector боится утерять данные при ошибке
    // и делая фоллбэк на МЕДЛЕННОЕ КОПИРОВАНИЕ:
    vec2.reserve(2);

    // Начиная с C++11, все деструкторы неявно помечены как noexcept(true)

    // Все конструкторы перемещение надо делать noexpect, функции swap также

    return 0;
}
