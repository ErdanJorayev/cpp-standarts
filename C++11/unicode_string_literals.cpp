// В этом файле мы изучим работу Unicode и Raw строковых литералов в C++11
// В отличие от wchar_t, типы char16_t и char32_t имеют строго фиксированный
// размер на всех платформах

// Ранее в другом файле мы изучали char_16t и char_32t, тут будут несколько моментов

#include <iostream>

int main()
{
    // 1. Префиксы кодировок UTF
    // По умолчанию C-строки имеют тип const char*

    // UTF-8: Переменная длина (от 1 до 4 байт на символ)
    // Латиница занимает 1 байт, кириллица — 2 байта
    const char* utf8 = u8"Hello UTF-8!";

    // UTF-16: Гарантированно 2 байта на элемент char16_t
    const char16_t* utf16 = u"Hello UTF-16!";

    // UTF-32: Гарантированно 4 байта на элемент char32_t (фиксированная длина под любой символ).
    const char32_t* utf32 = U"Hello UTF-32!";

    // 2. Raw String Literals (Сырые строки) — R"()"
    // Отключают экранирование. Все слэши '\' и кавычки '"' учитываются "как есть".
    const char* raw_path = R"(C:\Program Files\App\main.cpp)";

    // Можно комбинировать с UTF-8:
    const char* raw_utf8 = u8R"(Строка с "кавычками" и \n без экранирования)";

    std::cout << "UTF-8 string: " << utf8 << '\n';
    std::cout << "Raw Path:     " << raw_path << '\n';
    std::cout << "Raw UTF-8:    " << raw_utf8 << '\n';

    // Проверка гарантированных размеров во время компиляции
    static_assert(sizeof(char16_t) == 2, "char16_t must be 2 bytes");
    static_assert(sizeof(char32_t) == 4, "char32_t must be 4 bytes");

    return 0;
}
