#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int W, n;
    std::cin >> W >> n;
    std::vector<int> weights(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> weights[i];
    }
    
    std::vector<int> dp(W + 1, 0);
    for (int wi : weights) {
        if (wi > W) continue;
        for (int w = W; w >= wi; --w) {
            dp[w] = std::max(dp[w], dp[w - wi] + wi);
        }
    }

    std::cout << dp[W] << '\n';

    return 0;
}