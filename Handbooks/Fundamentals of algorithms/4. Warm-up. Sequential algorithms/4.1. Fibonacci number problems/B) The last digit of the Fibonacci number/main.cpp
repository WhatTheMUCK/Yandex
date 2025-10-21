#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n == 0) {
        std::cout << n << '\n';
        return 0;
    }

    int prev = 0, cur = 1;
    for (int i = 1; i < n; ++i) {
        int tmp = prev;
        prev = cur;
        cur = (prev + tmp) % 10;
    }

    std::cout << cur << '\n';
    return 0;
}