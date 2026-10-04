// В этом файле изучим тему инициализации в if и switch в С++17

#include <iostream>
#include <vector>
#include <map>

// В С++17 можно создавать и инициализировать данные
// прямо внутри скобок () if и switch

enum class Status { OK, NotFound, ServerError };

Status get_status() { return Status::NotFound; }

int main()
{
    // Объявляем и инициализируем, потом сравниваем
    if (int num = 23; num < 44)
        std::cout << num << '\n';

    // Можно и со сложными данными, классы например
    std::map<int, std::string> users = {{1, "Alice"}};
    if (auto it = users.find(1); it != users.end())
    {
        // 'it' видна только внутри этого блока
        std::cout << "Found: " << it->second << '\n';
    }
    else
    {
        // 'it' видна и в блоке else тоже!
        std::cout << "Not found\n";
    }

    // Короче как видно, область видимости данных сужается
    // в блок if, что очень удобно

    // Данная фича работает и с switch
    switch (Status s = get_status(); s)
    {
        case Status::OK:
            std::cout << "Success\n";
            break;
        case Status::NotFound:
            std::cout << "Error 404\n";
            break;
        default:
            std::cout << "Unknown error\n";
            break;
    }
    // Переменная 's' автоматически уничтожается здесь

    return 0;
}
