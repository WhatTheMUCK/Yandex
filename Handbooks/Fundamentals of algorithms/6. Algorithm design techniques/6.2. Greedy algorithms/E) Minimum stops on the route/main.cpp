#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    long long L, F;
    std::cin >> L >> F;

    std::vector<std::pair<long long, long long>> stations;
    for (int i = 0; i < n; ++i) {
        long long x, a;
        std::cin >> x >> a;
        stations.emplace_back(x, a);
    }

    stations.emplace_back(L, 0);
    std::sort(stations.begin(), stations.end());

    std::priority_queue<long long> max_heap;

    long long current_fuel = F;
    int refills = 0;
    long long prev_pos = 0;

    for (const auto& [pos, fuel] : stations) {
        long long distance = pos - prev_pos;

        while (current_fuel < distance) {
            if (max_heap.empty()) {
                std::cout << "-1\n";
                return 0;
            }
            current_fuel += max_heap.top();
            max_heap.pop();
            refills++;
        }

        current_fuel -= distance;
        prev_pos = pos;

        if (pos != L) {
            max_heap.push(fuel);
        }
    }

    std::cout << refills << '\n';
    return 0;
}