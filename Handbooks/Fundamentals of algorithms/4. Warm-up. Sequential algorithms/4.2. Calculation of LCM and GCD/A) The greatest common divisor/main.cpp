#include <iostream>

template <typename T>
T GCD(T lhs, T rhs) {
    if (lhs < rhs) {
        std::swap(lhs, rhs);
    }

    if (rhs == 0) {
        return lhs;
    }

    return GCD(lhs % rhs, rhs);
}

int main() {
    unsigned int a, b;
    std::cin >> a >> b;
    std::cout << GCD(a, b) << '\n';
    return 0;
}