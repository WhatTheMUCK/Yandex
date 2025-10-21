#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> timings(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> timings[i].first >> timings[i].second;
    }
    std::sort(timings.begin(), timings.end(), [](const auto & lhs, const auto & rhs){
        return std::tie(lhs.second, lhs.first) < std::tie(rhs.second, rhs.first);
    });

    std::vector<int> correctTimings;
    for (int i = 0; i < n; ++i) {
        if (!correctTimings.empty() && timings[i].first <= correctTimings.back()) {
            continue;
        }

        correctTimings.push_back(timings[i].second);
        continue;
    }

    std::cout << correctTimings.size() << '\n';
    for (size_t i = 0; i < correctTimings.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << correctTimings[i];
    }
    std::cout << '\n';

    return 0;
}