// В этом файле мы изучим делегирование и наследование конструкторов в C++11

#include <string>
#include <iostream>

// Делегирование конструкторов позволяет вызвать
// в списке инициализации одного конструктора другой конструктор этого же класса
class Car
{
private:
    std::string name;
    double speed;
    double price;
public:
    // Целевой (главный) конструктор
    Car(const std::string & n, double s, double p)
        : name(n), speed(s), price(p) {}

    // Делегирующий конструктор: вызываем главный конструктор в списке инициализации
    // Делегирующий конструктор НЕ может одновременно инициализировать
    // другие поля в списке инициализации (например, : Car(n, s, 33000.50), speed(0) - ОШИБКА),
    // но может изменять их в теле конструктора {}
    Car(const std::string & n, double s) : Car(n, s, 33000.50) {}

    void Show() const
    {
        std::cout << "Name: " << name << '\n'
                  << "Speed: " << speed << '\n'
                  << "Price: " << price << '\n';
    }
};

// Если базовый класс имел множество перегруженных конструкторов,
// их можно унаследовать одной строчкой через using
class Ferrari : public Car
{
public:
    // Наследуем ВСЕ конструкторы класса Car в Ferrari
    using Car::Car;

    // В C++03 пришлось бы вручную писать:
    // Ferrari(const std::string & n, double s, double p) : Car(n, s, p) {}
    // Ferrari(const std::string & n, double s) : Car(n, s) {}

    void Show() const
    {
        Car::Show();
    }
};

int main()
{
    Car bmw{"BMW", 300};             // Вызов делегирующего конструктора Car
    Ferrari ferrari("Ferrari", 330); // Вызов унаследованного конструктора Car через Ferrari

    bmw.Show();
    ferrari.Show();

    return 0;
}
