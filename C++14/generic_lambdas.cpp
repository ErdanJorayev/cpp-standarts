// В этом файле изучим работу generic lambdas в С++14

#include <iostream>
#include <algorithm>
#include <vector>

// До С++14, лямбда функции были строго типизированные,
// то есть надо было явно указывать тип аргумента функции
// В С++14, теперь можно помечать аргументы как auto
// и тип сам будет выведен

int main()
{
    // Вместо длинного: [](const std::pair<int, std::string>& p)
    auto print_pair = [](const auto& p)
    {
        std::cout << p.first << ": " << p.second << '\n';
    };

    print_pair(std::pair<int, const char *>(23, "My name"));

    std::vector<int> numbers = {3, 1, 4, 1, 5, 9};

    // Не нужно явно указывать (int n)
    std::for_each(numbers.begin(), numbers.end(), [](auto n) {
        std::cout << n << ' ';
    });

    std::cout << '\n';


    // Несколько авто-параметров (могут быть разными типами)
    auto add = [](auto a, auto b) {
        return a + b;
    };

    std::cout << add(5, 2.5) << '\n'; // int + double -> double (7.5)

    return 0;
}
