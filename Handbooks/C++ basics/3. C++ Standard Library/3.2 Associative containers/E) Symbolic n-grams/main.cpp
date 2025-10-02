#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
    int m, n;
    std::cin >> m >> n;
    std::unordered_map<std::string, int> mp;
    std::string input;
    for (int i = 0; i < m; ++i) {
        std::cin >> input;
        for (int i = 0; i < static_cast<int>(input.size()) - (n - 1); ++i) {
            ++mp[input.substr(i, n)];
        }
    }

    std::vector<std::pair<std::string, int>> vec(mp.begin(), mp.end());
    std::sort(vec.begin(), vec.end(), [](const auto & lhs, const auto & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first);
    });

    for (const auto & [key, value] : vec) {
        std::cout << key << " - " << value << '\n';
    }

    return 0;
}