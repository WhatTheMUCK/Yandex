#include <iostream>
#include <numeric>


int main() {
    long long a, b, c, d;
    std::cin >> a >> b >> c >> d;
    long long num = a * d + b * c;
    long long denum = b * d;
    long long gcd = std::gcd(num, denum);
    num /= gcd;
    denum /= gcd;
    std::cout << num << ' ' << denum << '\n';
    return 0;
}