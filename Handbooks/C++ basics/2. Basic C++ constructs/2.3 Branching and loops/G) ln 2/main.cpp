#include <iostream>

int main() {
    int n;
    std::cin >> n;
    double sum = 0;
    double sign = 1;
    for (int i = 1; i <= n; ++i) {
        sum += sign / i;
        sign *= -1;
    }
    std::cout << sum << '\n';
    return 0;
}