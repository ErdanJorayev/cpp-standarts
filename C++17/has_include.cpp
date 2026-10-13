// ============================================================================
// ПРОВЕРКА ЗАГОЛОВОЧНЫХ ФАЙЛОВ: __has_include (C++17)
// ============================================================================

#include <iostream>

// 1. Проверка наличия стандартных или экспериментальных библиотек
#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
    #define HAS_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
    #define HAS_FILESYSTEM 1
#else
    #define HAS_FILESYSTEM 0
#endif

// 2. Проверка наличия платформозависимых заголовков
#if __has_include(<unistd.h>)
    #include <unistd.h>
    constexpr bool has_posix_headers = true;
#else
    constexpr bool has_posix_headers = false;
#endif

int main() {
    std::cout << "=== __has_include check ===\n";

#if HAS_FILESYSTEM
    std::cout << "Filesystem header is available!\n";
    std::cout << "Current path: " << fs::current_path() << '\n';
#else
    std::cout << "Filesystem header is NOT available.\n";
#endif

    std::cout << "POSIX headers available: " << std::boolalpha << has_posix_headers << '\n';

    return 0;
}
