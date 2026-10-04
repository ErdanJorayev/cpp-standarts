// В этом файле изучим работу structure bindings, распаковка данных в С++17

#include <iostream>
#include <string>
#include <tuple>
#include <map>

// В С++17, можно распаковать структуры, массивы, классы и
// другие наборы данных за одну строчку

struct Planet
{
    std::string name = "Mars";
    int size = 20000;
};

int main()
{
    Planet mars;

    // Пишем auto, потом квадратные скобки
    // Внутри скобок пишем ровно то количество данных как в поле
    auto[nm, sz] = mars; // По сути распаковали данные

    std::cout << nm << " " << sz << '\n';

    int arr[2]{44, 55};

    auto[num1, num2] = arr;

    std::cout << num1 << " " << num2 << '\n';

    std::tuple<int, std::string> neptun{44000, "Neptun"};
    auto[szz, nmm] = neptun;

    std::cout << szz << " " << nmm << '\n';

    // Можно также делать ссылки и константы
    auto &[kek, lol] = neptun; // В таком случае можно прямо менять данные

    std::cout << kek << " " << lol << '\n';

    // Еще трюк
    std::map<int, std::string> status_codes = {{200, "OK"}, {404, "Not Found"}};

    // Раньше: for (const auto& pair : status_codes) { pair.first ... }
    for (const auto& [code, message] : status_codes)
        std::cout << "Code " << code << ": " << message << '\n';


    return 0;
}
