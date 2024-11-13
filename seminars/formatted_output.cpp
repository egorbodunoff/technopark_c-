#include <iostream>
#include <string_view>
#include <utility>

void println_impl(std::string_view fmt) { std::cout << fmt << std::endl; }

template <class T, class... Args>
void println_impl(std::string_view fmt, T&& value, Args&&... args) {
    size_t pos = fmt.find("{}");

    if (pos != std::string_view::npos) {
        std::cout << fmt.substr(0, pos);
        std::cout << std::forward<T>(value);

        println_impl(fmt.substr(pos + 2), std::forward<Args>(args)...);
    }
}

template <class T, class... Args>
void println(std::string_view fmt, T&& value, Args&&... args) {
    println_impl(fmt, std::forward<T>(value), std::forward<Args>(args)...);
}

int main() {
    auto res =
        std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();

    println("{}, {}! Unix timestamp right now: {}", "Hello", "world", res);

    return 0;
}
