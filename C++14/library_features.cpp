// Библиотечные обновления C++14 (Library Features)

#include <iostream>
#include <memory>         // std::make_unique
#include <utility>        // std::exchange, std::integer_sequence, std::index_sequence
#include <shared_mutex>   // std::shared_timed_mutex, std::shared_lock
#include <mutex>          // std::unique_lock
#include <tuple>          // std::tuple, std::get
#include <iomanip>        // std::quoted
#include <sstream>        // std::stringstream
#include <string>

// ----------------------------------------------------------------------------
// 1. std::make_unique (<memory>)
// Добавлена недостающая фабрика для std::unique_ptr (устраняет явный 'new',
// обеспечивает exception safety при вызове функций).
// ----------------------------------------------------------------------------
struct Data
{
    int value;
    Data(int v) : value(v) {}
};

void demo_make_unique()
{
    // Безопасное создание уникального указателя
    auto ptr = std::make_unique<Data>(42);
    std::cout << "[make_unique] Value: " << ptr->value << '\n';
}

// ----------------------------------------------------------------------------
// 2. std::shared_timed_mutex & std::shared_lock (<shared_mutex>)
// Разделяемая блокировка (Read-Write Lock):
// - Несколько потоков могут ЧИТАТЬ одновременно (std::shared_lock).
// - Только один поток может ПИСАТЬ эксклюзивно (std::unique_lock).
// ----------------------------------------------------------------------------
class ThreadSafeCounter
{
private:
    mutable std::shared_timed_mutex mutex_;
    int value_ = 0;

public:
    int get() const
    {
        // Shared lock: несколько читателей смотрят параллельно
        std::shared_lock<std::shared_timed_mutex> lock(mutex_);
        return value_;
    }

    void increment()
    {
        // Exclusive lock: только один писатель имеет доступ
        std::unique_lock<std::shared_timed_mutex> lock(mutex_);
        ++value_;
    }
};

// ----------------------------------------------------------------------------
// 3. std::integer_sequence / std::index_sequence (<utility>)
// Генератор последовательности индексов во время компиляции.
// Идеально для распаковки std::tuple в аргументы функции через variadic templates.
// ----------------------------------------------------------------------------
template <typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>)
{
    // Распаковка кортежа с помощью свёртки/инициализатора
    (void)std::initializer_list<int>{ (std::cout << std::get<Is>(t) << " ", 0)... };
    std::cout << '\n';
}

template <typename... Args>
void print_tuple(const std::tuple<Args...>& t)
{
    // Генерирует index_sequence<0, 1, 2, ...> по размеру tuple
    print_tuple_impl(t, std::make_index_sequence<sizeof...(Args)>{});
}

void demo_integer_sequence()
{
    auto my_tuple = std::make_tuple(10, "C++14", 3.14);
    std::cout << "[index_sequence] Tuple contents: ";
    print_tuple(my_tuple);
}

// ----------------------------------------------------------------------------
// 4. std::exchange (<utility>)
// Заменяет значение переменной на новое и ВОЗВРАЩАЕТ СТАРОЕ значение.
// Крайне удобно для перемещающих конструкторов (Move Constructors) и сброса флагов.
// ----------------------------------------------------------------------------
class Buffer
{
    int* data_ = nullptr;
    size_t size_ = 0;

public:
    Buffer(size_t size) : size_(size), data_(new int[size]) {}
    ~Buffer() { delete[] data_; }

    // Move-конструктор с помощью std::exchange
    Buffer(Buffer&& other) noexcept
        : data_(std::exchange(other.data_, nullptr)), // забирает data_ и ставит nullptr в other
          size_(std::exchange(other.size_, 0))         // забирает size_ и обнуляет other
    {}
};

void demo_exchange()
{
    int count = 100;
    // Присвоить 0, вернув старое значение (100)
    int old_count = std::exchange(count, 0);

    std::cout << "[exchange] Old: " << old_count << ", New: " << count << '\n';
}

// ----------------------------------------------------------------------------
// 5. std::quoted (<iomanip>)
// Утилита для обертывания строк в кавычки при IO-операциях.
// Автоматически экранирует внутренние кавычки при записи и корректно
// считывает строки с пробелами из потока.
// ----------------------------------------------------------------------------
void demo_quoted()
{
    std::stringstream ss;
    std::string original = "Hello \"World\" C++14";

    // Запись с экранированием
    ss << std::quoted(original);
    std::cout << "[quoted] Stream output: " << ss.str() << '\n';

    // Чтение с сохранением пробелов и кавычек
    std::string extracted;
    ss >> std::quoted(extracted);
    std::cout << "[quoted] Extracted string: " << extracted << '\n';
}

// ============================================================================
int main()
{
    demo_make_unique();
    demo_integer_sequence();
    demo_exchange();
    demo_quoted();

    ThreadSafeCounter counter;
    counter.increment();
    std::cout << "[shared_mutex] Counter: " << counter.get() << '\n';

    return 0;
}
