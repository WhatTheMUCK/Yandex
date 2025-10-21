#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end());
    std::vector<long long> dp(n, 0);
    dp[0] = k; // У самого левого нет вариантов кроме как присоединиться к потолочным коммуникациям
    for (size_t i = 1; i < x.size(); ++i) {
        dp[i] = dp[i - 1] + std::min(1ll * k, 1ll * (x[i] - x[i - 1]) * (x[i] - x[i - 1]));
    }

    std::cout << dp.back() << '\n';
    return 0;
}