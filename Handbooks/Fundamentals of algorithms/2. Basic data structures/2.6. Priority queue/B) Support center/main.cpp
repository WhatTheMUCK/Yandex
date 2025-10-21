#include <iostream>
#include <queue>

struct Compare {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
        return std::tie(lhs.first, rhs.second) < std::tie(rhs.first, lhs.second);
    }
};

int main() {
    int n;
    std::cin >> n;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
    for (int i = 0; i < n; ++i) {
        int d, w;
        std::cin >> d >> w;
        pq.push({w, d});
    }

    long long timeFirst = 0, timeSecond = 0;
    while (!pq.empty()) {
        auto [_, time1] = pq.top();
        pq.pop();
        timeFirst += time1;
        while (!pq.empty() && timeSecond < timeFirst) {
            auto [_, time2] = pq.top();
            pq.pop();
            timeSecond += time2;
        }
    }

    std::cout << std::max(timeFirst, timeSecond) << '\n';
    return 0;
}