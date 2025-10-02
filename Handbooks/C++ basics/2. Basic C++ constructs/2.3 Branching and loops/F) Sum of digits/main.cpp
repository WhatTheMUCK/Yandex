#include <iostream>
#include <numeric>

int main() {
    std::string number;
    std::cin >> number;
    std::cout << std::accumulate(number.begin(), number.end(), 0, [](int acc, const char & lhs) {
        return acc + (lhs - '0');
    }) << '\n';
    return 0;
}