#include <cstdio>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>

template <typename T>
std::string our_to_string(T val) {
    if constexpr (std::is_integral_v<T> && !std::is_same_v<T, bool>) {
        char buffer[64];
        std::snprintf(buffer, sizeof(buffer), "%llu", static_cast<unsigned long long>(val));

        return std::string(buffer);
    } else if constexpr (std::is_floating_point_v<T>) {
        char buffer[128];
        std::snprintf(buffer, sizeof(buffer), "%.6f", static_cast<double>(val));

        std::string result(buffer);

        if (result.find(".000000") != std::string::npos) {
            result = result.substr(0, result.find(".000000") + 2);
        }

        return result;
    } else if constexpr (std::is_same_v<T, bool>) {
        return val ? "true" : "false";
    } else if constexpr (std::is_convertible_v<T, const char*>) {
        return std::string(val);
    } else {
        static_assert(!std::is_same_v<T, T>,
                      "Unsupported type for our_to_string. Only integral, floating-point, bool, and C-string "
                      "types are supported.");
    }
}

// Примеры
int main() {
    std::cout << our_to_string(42) << "\n";
    std::cout << our_to_string(std::numeric_limits<uint64_t>::max()) << "\n";
    std::cout << our_to_string(1.0f) << "\n";
    std::cout << our_to_string(std::numeric_limits<double>::max()) << "\n";
    std::cout << our_to_string("Lorem ipsum dolor sit amet, consectetur adipiscing elit") << "\n";
    std::cout << our_to_string(true) << "\n";
    return 0;
}
