#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        ++mp[a];
    }

    std::vector<std::pair<int, int>> vec;
    for (const std::pair<const int, int> & pair : mp) {
        vec.push_back(pair);
    }

    std::sort(vec.begin(), vec.end(), [](const std::pair<int, int> & lhs, const std::pair<int, int> & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first); 
    });

    std::vector<int> answer;
    for (int i = 0; i < 3; ++i) {
        answer.push_back(vec[i].first); 
    }

    std::sort(answer.begin(), answer.end());

    for (int i = 0; i < 3; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}