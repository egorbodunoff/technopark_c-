#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "lru.hpp"

constexpr size_t EMBEDDING_SIZE = 64;

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<float> parseEmbedding(const std::string& str) {
    std::vector<float> embedding;
    std::stringstream ss(str);
    std::string number;
    while (ss >> number) {
        embedding.push_back(std::stof(number));
    }
    return embedding;
}

int main() {
    size_t N, Size;
    std::cin >> N >> Size;
    std::cin.ignore();

    LRUCache<std::string, std::vector<float>> cache(N, Size);

    std::string line;
    while (std::getline(std::cin, line)) {
        auto tokens = split(line, '\t');
        if (tokens.empty()) continue;

        const std::string& query = tokens[0];
        if (tokens.size() == 1) {
            auto embedding = cache.get(query);
            if (embedding) {
                for (size_t i = 0; i < embedding->size(); ++i) {
                    if (i > 0) std::cout << " ";
                    std::cout << (*embedding)[i];
                }
                std::cout << "\n";
            } else {
                std::cout << "!NOEMBED!\n";
            }
        } else if (tokens.size() == 2) {
            try {
                // Разбиваем строку эмбеддинга на части
                auto string_tokens = split(tokens[1], ' ');
                std::vector<float> embedding;

                // Преобразуем каждую часть в float
                for (const auto& token : string_tokens) {
                    embedding.push_back(std::stof(token));
                }

                // Проверяем размер эмбеддинга
                if (embedding.size() != EMBEDDING_SIZE) {
                    std::cout << "!STORERR!\n";
                    continue;
                }

                // Сохраняем в кэше
                if (cache.put(query, embedding)) {
                    std::cout << "!STORED!\n";
                } else {
                    std::cout << "!STORERR!\n";
                }
            } catch (const std::exception& e) {
                std::cout << "!STORERR!\n";
            }
        }
    }

    return 0;
}
