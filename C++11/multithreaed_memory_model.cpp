// В этом файле изучим работу многопоточной модели памяти в C++11
// В целом обзор на многопоточность будет в другом проекте, ибо тема большая.

#include <iostream>
#include <thread> // Для создание самого потока
#include <atomic> // Для атомарных операций
#include <vector>
#include <cassert>

// ============================================================================
// ШАГ 1: Memory Location, Data Race и Атомарность
// ============================================================================
// Data Race (Гонка данных) — это Undefined Behavior (UB)!
// Возникает, когда 2+ потока одновременно обращаются к одной Memory Location,
// хотя бы один пишет, и нет синхронизации.
// Причина: обычная переменная требует 3 ассм-команды (Read-Modify-Write).

int unsafe_counter = 0;              // Обычная переменная -> Data Race (UB)
std::atomic<int> safe_counter{0};    // Атомарная переменная -> 1 неделимая инструкция (LOCK)

void demo_step1_data_race()
{
    std::cout << "=========================================================\n";
    std::cout << "1. Data Race (UB) vs std::atomic (Аппаратная атомарность)\n";
    std::cout << "=========================================================\n";

    auto task = []()
    {
        for (int i = 0; i < 100000; ++i)
        {
            // ОПАСНО: Потоки прерывают RMW-цикл друг друга
            unsafe_counter++;

            // БЕЗОПАСНО: Аппаратная атомарная инструкция (LOCK XADD на x86)
            safe_counter.fetch_add(1, std::memory_order_relaxed);
        }
    };

    std::thread t1(task);
    std::thread t2(task);
    t1.join();
    t2.join();

    std::cout << "Ожидаемый результат: 200000\n";
    std::cout << "Unsafe counter (Data Race): " << unsafe_counter << " (потеря данных!)\n";
    std::cout << "Safe counter (std::atomic): " << safe_counter << " (строго 200000)\n\n";
}

// ============================================================================
// ШАГ 2: Lock-Free свойства и CAS-петли (Compare-And-Swap)
// ============================================================================
// CAS (compare_exchange_weak/strong) — основа всех Lock-Free структур данных.
// Проверяет, поддерживает ли железо атомики без мьютексов под капотом.



void demo_step2_lock_free_and_cas()
{
    std::cout << "=========================================================\n";
    std::cout << "2. Lock-Free свойства и CAS-петля (Compare-And-Swap)\n";
    std::cout << "=========================================================\n";

    std::atomic<int> atomic_int{10};

    // is_lock_free() показывает, делает ли CPU операцию аппаратной инструкцией
    std::cout << "std::atomic<int> is lock-free?         "
              << std::boolalpha << atomic_int.is_lock_free() << '\n';

    // Идиома CAS-петли: атомарно меняем значение только если оно не измнено другим потоком
    int expected = atomic_int.load();
    int desired = 100;

    // Сравнивает atomic_int с expected.
    // Если равны -> присваивает desired и возвращает true.
    // Если не равны -> перезаписывает expected новым значением и возвращает false.
    while (!atomic_int.compare_exchange_weak(expected, desired))
    {
        // Повторяем попытку, если другой поток перехватил запись
    }

    std::cout << "Результат CAS-перезаписи: " << atomic_int.load() << "\n\n";
}

// ============================================================================
// ШАГ 3: Порядок памяти (Instruction Reordering & Acquire-Release)
// ============================================================================
// Компилятор и CPU переставляют инструкции местами ради скорости.
// Acquire-Release семантика запрещает переупорядочивание вокруг барьера
// и создает связь Synchronizes-With между потоками.

int payload_data = 0; // Обычные неатомарные данные
std::atomic<bool> ready_flag{false};

void producer()
{
    payload_data = 42; // 1. Готовим данные

    // 2. Публикуем флаг с memory_order_release.
    // БАРЬЕР: Ни одна запись ДО этой строки НЕ может быть переставлена НИЖЕ её!
    ready_flag.store(true, std::memory_order_release);
}

void consumer() {
    // 3. Читаем флаг с memory_order_acquire.
    // БАРЬЕР: Ни одно чтение ПОСЛЕ этой строки НЕ может быть поднято ВЫШЕ её!
    while (!ready_flag.load(std::memory_order_acquire))
    {
        std::this_thread::yield();
    }

    // 4. Гарантия Happens-Before: мы ГАРАНТИРОВАННО видим payload_data == 42
    std::cout << "=========================================================\n";
    std::cout << "3. Happens-Before & Acquire-Release Синхронизация\n";
    std::cout << "=========================================================\n";
    std::cout << "Полученные данные: " << payload_data << " (Переупорядочивание предотвращено!)\n\n";
}

// ============================================================================
// ШАГ 4: Relaxed Memory Order & Thread-Local Storage (thread_local)
// ============================================================================
// memory_order_relaxed: даёт только атомарность, БЕЗ барьеров памяти (самый быстрый).
// thread_local: у КАЖДОГО потока своя личная копия переменной (нет общего доступа -> нет Data Race).

thread_local int thread_specific_id = 0; // Своя копия в каждом потоке
std::atomic<int> relaxed_counter{0};

void worker_thread(int id)
{
    thread_specific_id = id; // Изолированная локальная память потока

    for (int i = 0; i < 1000; ++i)
    {
        // Атомарный инкремент БЕЗ синхронизации кэшей/барьеров
        relaxed_counter.fetch_add(1, std::memory_order_relaxed);
    }

    std::cout << "Поток " << id << " имеет thread_local ID: " << thread_specific_id << '\n';
}

void demo_step4_relaxed_and_tls()
{
    std::cout << "=========================================================\n";
    std::cout << "4. Relaxed Memory Order & Thread-Local Storage\n";
    std::cout << "=========================================================\n";

    std::thread t1(worker_thread, 101);
    std::thread t2(worker_thread, 202);
    t1.join();
    t2.join();

    std::cout << "Relaxed Counter (2000 итераций): " << relaxed_counter.load() << "\n\n";
}

// ============================================================================
// MAIN: Запуск всей многопоточной модели памяти C++11
// ============================================================================
int main()
{
    demo_step1_data_race();
    demo_step2_lock_free_and_cas();

    std::thread prod(producer);
    std::thread cons(consumer);
    prod.join();
    cons.join();

    demo_step4_relaxed_and_tls();

    return 0;
}
