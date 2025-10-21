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

template <typename T>
T LCM(T lhs, T rhs) {
    return lhs * rhs / GCD(lhs, rhs);
}

int main() {
    long long a, b;
    std::cin >> a >> b;
    std::cout << LCM(a, b) << '\n';
    return 0;
}