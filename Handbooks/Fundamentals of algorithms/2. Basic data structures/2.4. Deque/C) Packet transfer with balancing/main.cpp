#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::priority_queue<
        std::pair<long long, int>,
        std::vector<std::pair<long long, int>>,
        std::greater<std::pair<long long, int>>> pq;

    for (int i = 0; i < k; ++i) {
        pq.push({0, i});
    }

    std::vector<long long> result(n);

    for (int i = 0; i < n; ++i) {
        long long t, d;
        std::cin >> t >> d;

        auto [readyTime, serverId] = pq.top();
        pq.pop();

        long long start = std::max(readyTime, t);
        long long finish = start + d;
        result[i] = finish;

        pq.push({finish, serverId});
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << result[i];
    }
    std::cout << '\n';

    return 0;
}