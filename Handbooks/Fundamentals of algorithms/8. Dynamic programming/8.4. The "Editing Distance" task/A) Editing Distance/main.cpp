#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::string first, second;
    std::cin >> first >> second;
    std::vector<std::vector<int>> dp(first.size() + 1, std::vector<int>(second.size() + 1, 0));
    for (size_t i = 1; i <= first.size(); ++i) {
        dp[i][0] = i;
    }

    for (size_t i = 1; i <= second.size(); ++i) {
        dp[0][i] = i;
    }

    for (size_t i = 1; i <= first.size(); ++i) {
        for (size_t j = 1; j <= second.size(); ++j) {
            int insertion = dp[i][j - 1] + 1;
            int deletion = dp[i - 1][j] + 1;
            int match = dp[i - 1][j - 1];
            int mismatch = dp[i - 1][j - 1] + 1;
            if (first[i - 1] == second[j - 1]) {
                dp[i][j] = std::min({insertion, deletion, match});
            } else {
                dp[i][j] = std::min({insertion, deletion, mismatch});
            } 
        }
    }

    std::cout << dp[first.size()][second.size()] << '\n';

    return 0;
}