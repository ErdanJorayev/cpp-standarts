// В этом файле изучим Guaranteed Copy Elision и Temporary Materialization (C++17)

#include <iostream>

struct CantTouchThis
{
    int value;

    CantTouchThis(int v) : value(v) {}

    // Полностью запрещаем копирование и перемещение!
    CantTouchThis(const CantTouchThis&) = delete;
    CantTouchThis(CantTouchThis&&) = delete;
};

// RVO (Return Value Optimization) — ГАРАНТИРОВАНО в C++17!
// Возврат временного анонимного объекта (prvalue).
// В C++17 prvalue — это не объект, а лишь "рецепт/инструкция для инициализации".
CantTouchThis make_object()
{
    return CantTouchThis{777}; // Никаких временных объектов не создаётся!
}

// NRVO (Named Return Value Optimization) — НЕ гарантировано стандартом!
// Если мы создаем ИМЕНОВАННУЮ локальную переменную внутри функции:
/*
CantTouchThis make_named_object()
{
    CantTouchThis obj{555}; // У переменной есть имя 'obj'
    return obj;            // ❌ НЕ скомпилируется! Для NRVO требуется
                           // доступный move/copy конструктор, даже если
                           // компилятор фактически оптимизирует вызов.
}
*/

int main()
{
    // Guaranteed Copy Elision: компилятор выделяет память под 'target'
    // и конструирует объект НАПРЯМУЮ по этому адресу.
    //
    // Temporary Materialization (Материализация): момент, когда "рецепт" (prvalue)
    // превращается в реальный объект в памяти (при присваивании переменной 'target').
    CantTouchThis target = make_object();

    std::cout << "Value: " << target.value << '\n'; // 777

    return 0;
}
