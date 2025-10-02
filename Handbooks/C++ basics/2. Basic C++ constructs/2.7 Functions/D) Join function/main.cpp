#include <iostream>
#include <vector>
#include <string>

std::string Join(const std::vector<std::string>& tokens, char delimiter) {
    std::string answer;
    size_t n = tokens.size();
    if (n == 0) {
        return answer;
    }

    for (size_t i = 1; i < n; ++i) {
        answer += tokens[i - 1] + delimiter;
    }

    answer += tokens.back();

    return answer;
}

int main() {
    std::cout << Join({"What", "is", "your", "name?"}, '_') << '\n';
    std::cout << Join({"What"}, '_') << '\n';
    std::cout << Join({}, '_') << '\n';
    return 0;
}