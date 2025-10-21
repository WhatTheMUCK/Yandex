#include <iostream>
#include <vector>
#include <numeric>


int main() {
    int n;
    std::cin >> n;
    std::vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> v[i];
    }
    int V = std::accumulate(v.begin(), v.end(), 0);
    if (V % 3 != 0) {
        std::cout << "0\n";
        return 0;
    }

    V /= 3;
    std::vector<std::vector<std::vector<bool>>> dp(n + 1, std::vector<std::vector<bool>>(V + 1, std::vector<bool>(V + 1, false)));
    dp[0][0][0] = true;
    for (int i = 1; i <= n; ++i) {
        for (int s1 = 0; s1 <= V; ++s1) {
            for (int s2 = 0; s2 <= V; ++s2) {
                dp[i][s1][s2] = dp[i - 1][s1][s2];
                if (s1 >= v[i - 1]) {
                    dp[i][s1][s2] = dp[i][s1][s2] || dp[i - 1][s1 - v[i - 1]][s2];
                }
                if (s2 >= v[i - 1]) {
                    dp[i][s1][s2] = dp[i][s1][s2] || dp[i - 1][s1][s2 - v[i - 1]];
                }
            }
        }
    }

    std::cout << dp[n][V][V] << '\n';
    
    return 0;
}