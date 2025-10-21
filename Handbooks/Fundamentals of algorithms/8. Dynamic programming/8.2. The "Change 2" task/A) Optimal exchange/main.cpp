#include <iostream>
#include <vector>
#include <limits>


int main() {
    int money;
    std::cin >> money;
    std::vector<int> nominals = {1, 3, 4};
    int infinity = std::numeric_limits<int>::max();
    std::vector<int> dp(money + 1, infinity);
    dp[0] = 0;
    for (int i = 1; i <= money; ++i) {
        for (int nominal : nominals) {
            if ((i - nominal) < 0) {
                break;
            }
            dp[i] = std::min(dp[i], dp[i - nominal] + 1);
        }
    }
    std::cout << dp[money] << '\n';
    return 0;
}