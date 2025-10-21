#include <iostream>
#include <algorithm>
__uint128_t MOD = 1;

int main() {
    for (int i = 0; i < 19; ++i) {
        MOD *= 10;
    }

    long long a, b;
    int k;
    std::cin >> a >> b >> k;
    __uint128_t temp = 1;
    for (int i = 63; i >= 0; --i) {
        temp = (temp * temp) % MOD;
        if ((b & (1ll << i)) > 0) {
            temp = (temp * a) % MOD;
        }
    }
    std::string answer;
    while (k > 0) {
        answer.push_back(temp % 10 + '0');
        temp /= 10;
        --k;
    }
    std::reverse(answer.begin(), answer.end());
    std::cout << answer << '\n';
    return 0;
}