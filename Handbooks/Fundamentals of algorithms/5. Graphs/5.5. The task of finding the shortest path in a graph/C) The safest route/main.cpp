#include <iostream>
#include <queue>
#include <unordered_map>
#include <limits>


long long Djkstra(int start, int end,
                  const std::unordered_map<int, std::unordered_map<int, int>> & graph) {

    int n = static_cast<int>(graph.size());
    long long infinity = std::numeric_limits<long long>::max();
    std::vector<long long> distances(n, infinity);
    std::vector<bool> visited(n, false);
    std::priority_queue<std::pair<long long, int>,
                        std::vector<std::pair<long long, int>>,
                        std::greater<std::pair<long long, int>>> pq;
    distances[start] = 0ll;
    visited[start] = true;
    pq.push({0ll, start});
    
    while (!pq.empty()) {
        auto [curDistance, curVertex] = pq.top();
        pq.pop();

        if (curVertex == end) {
            return curDistance;
        }

        for (auto [neighbour, distance] : graph.at(curVertex)) {
            long long tempDistane = distances[curVertex] + distance;
            if (tempDistane < distances[neighbour]) {
                distances[neighbour] = tempDistane;
                pq.push({tempDistane, neighbour});
            }
        }
    }

    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m, q;
    std::cin >> n >> m >> q;
    std::unordered_map<int, std::unordered_map<int, int>> graph;    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        --u, --v;
        graph[u][v] = w;
        graph[v][u] = w;
    }

    for (int i = 0; i < n; ++i) {
        if (!graph.contains(i)) {
            graph[i] = {};
        }
    }

    for (int i = 0; i < q; ++i) {
        int x, y;
        std::cin >> x >> y;
        --x, --y;
        long long amount = Djkstra(x, y, graph);
        std::cout << amount << '\n';
    }
    return 0;
}