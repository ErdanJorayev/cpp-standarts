// В этом файле изучим работу final и override

// override используется при наследовании. Он нужен
// чтобы проверить, совпадают ли сигнатуры метода
// производного класса с методом базового класса
class Base
{
public:
    virtual void sound(int x) {}
};
class Derived : public Base
{
public:
    // Будет ошибка компиляции, сигнатура не совпадает
    // void sound(double x) override {}

    void sound(int x) override {} // Сигнатуры совпадают
};

// final не позволит наследоваться от этого класса
class Animal final
{
};

// class Lion : public Animal {}; Будет ошибка компиляции

// Так final запрещает переопределять виртуальный метод
class Clock
{
public:
    virtual void tick() final; // дочерние классы не смогут переопределить
};

class Timer : public Clock
{
public:
    // void tick() override; Будет ошибка компиялции
};


int main()
{
    return 0;
}
