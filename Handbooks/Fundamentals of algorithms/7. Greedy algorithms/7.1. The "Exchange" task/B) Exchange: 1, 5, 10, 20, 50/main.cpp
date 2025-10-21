#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int money;
    std::cin >> money;
    std::vector<int> nominals = {0, 0, 0, 0, 0};
    std::unordered_map<int, int> mp = {
        {0, 50}, {1, 20}, {2, 10}, {3, 5}, {4, 1} 
    };

    for (size_t i = 0; i < nominals.size(); ++i) {
        nominals[i] += money / mp[i];
        money %= mp[i];
    }

    std::cout << std::accumulate(nominals.begin(), nominals.end(), 0ll) << '\n';
    bool first = true;
    for (size_t i = 0; i < nominals.size(); ++i) {
        for ( ;nominals[i] > 0; --nominals[i]) {
            if (!first) std::cout << ' ';
            std::cout << mp[i];
            first = false;
        }
    }
    std::cout << '\n';

    return 0;
}