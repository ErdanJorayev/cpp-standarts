// В этом файле изучим инициализацию полей класса по месту объявления
// (In-class member initializers / Brace-or-equal initializers) в C++11

#include <iostream>

class STM32
{
private:
    unsigned int flash_size = 256; // Equal-initializer (=):
    unsigned int rom_size{64};     // Brace-initializer ({}):
public:
    // Конструктор по умолчанию использует дефолтные значения 256 и 64
    STM32() = default;

    // Параметризованный конструктор переопределяет полей
    STM32(unsigned int f, unsigned int r)
        : flash_size(f), rom_size(r) {}

    void show() const
    {
        std::cout << "Flash memory: " << flash_size << " KB\n";
        std::cout << "ROM: " << rom_size << " KB\n";
    }
};

int main()
{
    STM32 id1;
    STM32 id2(512, 128);

    id1.show();
    id2.show();

    return 0;
}
