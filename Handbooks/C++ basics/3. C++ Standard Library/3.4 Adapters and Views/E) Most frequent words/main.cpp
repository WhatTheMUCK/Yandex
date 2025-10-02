#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>


int main() {
    size_t k;
    std::cin >> k;
    std::unordered_map<std::string, int> mp;
    std::string input;
    while (std::cin >> input) {
        ++mp[input];
    }

    std::vector<std::pair<std::string, int>> vec(mp.begin(), mp.end());
    std::sort(vec.begin(), vec.end(), [](const auto & lhs, const auto & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first);
    });

    for (size_t i = 0; i < k && i < vec.size(); ++i) {
        std::cout << vec[i].first << '\t' << vec[i].second << '\n';
    }

    return 0;
}