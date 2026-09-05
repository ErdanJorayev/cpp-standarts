// В этом файле изучим работу nullptr в C++11

#include <iostream>
#include <cstddef> // Хедер для std::nullptr_t
// До С++11, вместо nullptr применялся NULL
// NULL по сути обычный макрос который был просто 0 или __null
// А число 0 имеет по умолчанию тип int
// nullptr решил проблему с типом и имеет тип nullptr_t

// Можно создать даже функции которые принимают только nullptr

void fun(std::nullptr_t)
{
    std::cout << "nullptr передан\n";
}

void fun(int n)
{
    std::cout << "Передано число\n";
}

int main()
{
    int * old_style = NULL; // Старый стиль
    int * ptr = nullptr;    // Новый

    fun(32);
    fun(nullptr);
    //fun(NULL); Ошибка компиляции, компилятор может NULL перевести в nullptr
    // но тут возникает неоднозначность, ибо можно перевести и в число

    return 0;
}
