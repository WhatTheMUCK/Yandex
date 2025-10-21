#include <iostream>
#include <string>
#include <algorithm>

using u128 = __uint128_t;

u128 modMult(u128 a, u128 b, u128 mod) {
    return (a * b) % mod;
}

u128 modPow(u128 base, unsigned long long exp, u128 mod) {
    if (exp == 0) return 1 % mod;
    if (exp % 2 == 0) {
        u128 half = modPow(base, exp / 2, mod);
        return modMult(half, half, mod);
    } else {
        return modMult(base, modPow(base, exp - 1, mod), mod);
    }
}

int main() {
    unsigned long long a, b;
    int K;
    std::cin >> a >> b >> K;

    u128 mod = 1;
    for (int i = 0; i < K; ++i) {
        mod *= 10;
    }

    u128 result = modPow(a % mod, b, mod);

    std::string s = "";
    for (int i = 0; i < K; ++i) {
        s += char('0' + (result % 10));
        result /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s << '\n';
}