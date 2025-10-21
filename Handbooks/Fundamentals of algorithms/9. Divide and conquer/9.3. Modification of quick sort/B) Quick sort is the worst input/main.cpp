#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> evens, odds;

    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 0) {
            evens.push_back(i);
        } else {
            odds.push_back(i);
        }
    }

    // Выводим сначала чётные, потом нечётные
    bool first = true;
    for (int x : evens) {
        if (!first) std::cout << " ";
        std::cout << x;
        first = false;
    }
    for (int x : odds) {
        if (!first) std::cout << " ";
        std::cout << x;
        first = false;
    }
    std::cout << '\n';

    return 0;
}