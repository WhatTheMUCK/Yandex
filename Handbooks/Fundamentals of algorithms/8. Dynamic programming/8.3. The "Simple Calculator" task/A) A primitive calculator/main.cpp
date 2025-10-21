#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    int infinity = std::numeric_limits<int>::max();
    std::vector<int> dp(n + 1, infinity), parents(n + 1);
    dp[1] = 0;
    parents[1] = 1;
    for (int i = 2; i <= n; ++i) {
        int parent = i - 1;
        dp[i] = std::min(dp[i], dp[i - 1] + 1);
        if (i % 2 == 0 && dp[i / 2] + 1 < dp[i]) {
            parent = i / 2;
            dp[i] = dp[i / 2] + 1;
        }

        if (i % 3 == 0 && dp[i / 3] + 1 < dp[i]) {
            parent = i / 3;
            dp[i] = dp[i / 3] + 1;
        }

        parents[i] = parent;
    }

    std::cout << dp[n] << '\n';
    std::vector<int> answer;
    int curIndex = n;
    while (curIndex != parents[curIndex]) {
        answer.push_back(curIndex);
        curIndex = parents[curIndex];
    }
    answer.push_back(1);
    std::reverse(answer.begin(), answer.end());
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}