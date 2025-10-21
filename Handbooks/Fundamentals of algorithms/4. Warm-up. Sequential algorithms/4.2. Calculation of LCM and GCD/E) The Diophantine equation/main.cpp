#include <iostream>
#include <numeric>


int main() {
    int a, b, c;
    std::cin >> a >> b >> c;
    std::cout << (c % std::gcd(a, b) == 0 ? "YES" : "NO") << '\n';
    return 0;
}