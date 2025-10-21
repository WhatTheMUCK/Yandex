#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, typename V>
std::istream & operator>>(std::istream & is, std::pair<T, V> & rhs) {
    return is >> rhs.first >> rhs.second;
} 

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> timings(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> timings[i];
    }

    std::sort(timings.begin(), timings.end(), [](const auto & lhs, const auto & rhs) {
        return std::tie(lhs.second, lhs.first) < std::tie(rhs.second, rhs.first);
    });

    int answer = 0;
    int r = 0;
    for (int i = 0; i < n; ++i) {
        auto [l1, r1] = timings[i];
        if (l1 > r) {
            ++answer;
            r = r1;
        }
    }

    std::cout << answer << '\n';
    return 0;
}