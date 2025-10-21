#include <iostream>
#include <queue>

struct Compare {
    bool operator()(const std::tuple<long long, int, int>& lhs, const std::tuple<long long, int, int>& rhs) const {
        return std::tie(std::get<0>(rhs), std::get<1>(rhs)) < std::tie(std::get<0>(lhs), std::get<1>(lhs));
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::priority_queue<std::tuple<long long, int, int>, 
                        std::vector<std::tuple<long long, int, int>>,
                        Compare> pq;
    for (int i = 0; i < n; ++i) {
        int id, p, s;
        std::cin >> id >> p >> s;
        pq.push({s, id, p});
    }

    while (m > 0) {
        auto [s, id, p] = pq.top();
        pq.pop();
        std::cout << id << '\n';
        pq.push({s + p, id, p});
        --m;
    }

    return 0;
}