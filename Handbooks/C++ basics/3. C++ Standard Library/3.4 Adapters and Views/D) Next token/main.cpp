#include <iostream>
#include <string>
#include <string_view>

bool NextToken(std::string_view & sv, const char delimiter, std::string_view & token) {
    size_t findPos = sv.find(delimiter);
    if (findPos != std::string::npos) {
        token = sv.substr(0, findPos);
        sv = sv.substr(findPos + 1);
    } else {
        token = sv;
        sv = "";
    }
    
    return !token.empty();
}

int main() {
    std::string_view sv = "Hello world and good bye";

    const char delimiter = ' ';
    std::string_view token;

    // Делим строку на токены по разделителю и перебираем эти токены:
    while (NextToken(sv, delimiter, token)) {
        // обрабатываем очередной token
        // например, печатаем его на экране:
        std::cout << token << "\n";
    }
}