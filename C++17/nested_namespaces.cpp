// В этом файле изучим работу nested namespaces в С++17

#include <iostream>

// 1. СРАВНЕНИЕ СИНТАКСИСА
// Как было ДО C++17: "Лесенка" скобок и отступов
namespace LegacyEngine
{
    namespace Graphics
    {
        namespace Direct3D
        {
            void legacy_draw()
            {
                std::cout << "Legacy D3D Draw\n";
            }
        }
    }
}

// Как стало В C++17: Компактное объявление цепочки
namespace ModernEngine::Graphics::Vulkan
{
    void modern_draw()
    {
        std::cout << "Modern Vulkan Draw\n";
    }
}


// 2. РАБОТА С НЕСКОЛЬКИМИ УРОВНЯМИ
namespace Application::UI
{
    // Объявление элемента на уровне UI
    struct Window
    {
        int width = 1920;
        int height = 1080;
    };
}

namespace Application::UI::Widgets
{
    // Объявление элемента на уровне UI::Widgets
    void draw_button(const Application::UI::Window& win)
    {
        std::cout << "Button rendered in window " << win.width << "x" << win.height << '\n';
    }
}


// 3. ПРИМЕНЕНИЕ В MAIN
int main()
{
    // Доступ через цепочку пространств имён
    LegacyEngine::Graphics::Direct3D::legacy_draw();
    ModernEngine::Graphics::Vulkan::modern_draw();

    // Работа со структурированными вложенными пространствами
    Application::UI::Window main_window;
    Application::UI::Widgets::draw_button(main_window);

    return 0;
}
