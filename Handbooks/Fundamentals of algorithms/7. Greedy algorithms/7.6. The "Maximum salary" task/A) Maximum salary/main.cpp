#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }
    std::sort(numbers.begin(), numbers.end(), [](const auto & lhs, const auto & rhs){
        return (lhs + rhs > rhs + lhs);
    });

    for (const auto & number : numbers) {
        std::cout << number;
    }
    std::cout << '\n';

    return 0;
}