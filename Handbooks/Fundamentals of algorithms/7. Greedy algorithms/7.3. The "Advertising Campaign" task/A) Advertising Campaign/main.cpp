#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> prices(n), clicks(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> prices[i];
    }
    std::sort(prices.begin(), prices.end(), std::greater<int>());
    for (int i = 0; i < n; ++i) {
        std::cin >> clicks[i];
    }
    std::sort(clicks.begin(), clicks.end(), std::greater<int>());
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        answer += 1ll * prices[i] * clicks[i];
    }

    std::cout << answer << '\n';
    return 0;
}