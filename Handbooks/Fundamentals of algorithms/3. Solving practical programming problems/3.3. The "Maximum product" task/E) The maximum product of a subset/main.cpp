#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<long long, long long>> vec(n);
    for (int i = 0 ; i < n; ++i) {
        long long value;
        std::cin >> value;
        vec[i] = {value, i + 1};
    }

    std::sort(vec.begin(), vec.end());

    std::vector<long long> answer;
    int l = 0, r = n - 1;
    
    while (r >= 0 && vec[r].first > 0) {
        answer.push_back(vec[r].second);
        --r;
    }

    while (l + 1 <= r && vec[l].first < 0 && vec[l + 1].first < 0) {
        answer.push_back(vec[l].second);
        answer.push_back(vec[l + 1].second);
        l += 2;
    }

    if (answer.empty()) {
        answer.push_back(vec[r].second);
    }
    std::sort(answer.begin(), answer.end());

    for (long long ind : answer) {
        std::cout << ind << ' ';
    }
    std::cout << '\n';
    return 0;
}