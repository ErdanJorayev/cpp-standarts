// В этом файле изучим работу цикла for в диапазоне в C++11

#include <iostream>
#include <vector>


// for в диапазоне применяется для работы с контейнерами
// Чтобы с ним работать, нужно чтобы у класса были методы begin(), end()
// for в диапазоне работает только тогда когда у контейнера уже есть данные
int main()
{
    std::vector<int> v1{21, 22, 23, 24};


    // Обычное чтение данных
    for (const auto & vec : v1)
        std::cout << vec << ' ';
    std::cout << '\n';

    // Запись/изменение значений элементов вектора по ссылке (auto&)
    for (auto & vec : v1)
        vec *= 2; // Умножаем каждый элемент на 2

    // Обход обычного C-массива (работает автоматически благодаря std::begin/end)
    int raw_array[] = {1, 2, 3, 4, 5};
    std::cout << "Raw C-array traversal:\n";
    for (int val : raw_array)
        std::cout << val << " ";

    return 0;
}
