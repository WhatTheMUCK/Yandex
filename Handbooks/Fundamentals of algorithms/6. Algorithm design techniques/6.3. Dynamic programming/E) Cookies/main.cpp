#include <iostream>
#include <vector>

const long long MOD = 1'000'000'007;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    if (n == 1) {
        std::cout << "3\n";
        return 0;
    }

    // Кодируем состояние как 3 * first + second, где A=0, B=1, C=2
    std::vector<long long> dp(9, 1); // все 9 пар: AA, AB, ..., CC

    for (int i = 3; i <= n; ++i) {
        std::vector<long long> new_dp(9, 0);
        for (int cur = 0; cur < 9; ++cur) {
            int first = cur / 3;       // первый символ текущего состояния

            for (int state = 0; state < 3; ++state) {
                if (first == state) continue;

                int prev = state * 3 + first;
                new_dp[cur] = (new_dp[cur] + dp[prev]) % MOD;
            }
        }
        dp = std::move(new_dp);
    }

    long long ans = 0;
    for (long long x : dp) {
        ans = (ans + x) % MOD;
    }
    std::cout << ans << '\n';
}