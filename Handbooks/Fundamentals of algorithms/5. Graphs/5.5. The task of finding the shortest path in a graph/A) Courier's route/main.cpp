#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <climits>
#include <queue>


long long DjkstraWithPath(int start, int finish,
                          const std::unordered_map<int, std::unordered_map<int, int>>& graph,
                          std::vector<int>& outPath) {
    int n = static_cast<int>(graph.size());
    if (n == 0) return 0;

    std::vector<long long> distances(n, LLONG_MAX);
    std::vector<int> parents(n, -1);
    std::vector<bool> visited(n, false);
    
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<>> pq;
    distances[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [_, curVertex] = pq.top();
        pq.pop();

        if (curVertex == finish) break;

        for (auto [neighbour, distance] : graph.at(curVertex)) {
            long long tempDist = distances[curVertex] + distance;
            if (tempDist < distances[neighbour]) {
                distances[neighbour] = tempDist;
                parents[neighbour] = curVertex;
                pq.push({tempDist, neighbour}); 
            }
        }
    }

    outPath.clear();
    int cur = finish;
    std::vector<int> temp;
    while (cur != -1 && cur != start) {
        temp.push_back(cur);
        cur = parents[cur];
    }
    if (cur != start) {
        return LLONG_MAX;
    }

    for (int i = static_cast<int>(temp.size()) - 1; i >= 0; --i) {
        outPath.push_back(temp[i]);
    }

    return distances[finish];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, V;
    std::cin >> n >> m >> V;
    --V;

    int O1, O2, O3;
    std::cin >> O1 >> O2 >> O3;
    --O1; --O2; --O3;

    std::unordered_map<int, std::unordered_map<int, int>> graph;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c;
        --u; --v;
        graph[u][v] = c;
        graph[v][u] = c;
    }

    std::vector<int> orders = {O1, O2, O3};
    std::sort(orders.begin(), orders.end());
    long long bestTotal = LLONG_MAX;
    std::vector<int> bestFullPath;

    do {
        std::vector<int> sequence = {V, orders[0], orders[1], orders[2], V};
        std::vector<int> fullPath = {V};
        long long totalDist = 0;
        bool valid = true;

        for (int i = 0; i < 4; ++i) {
            int from = sequence[i];
            int to = sequence[i + 1];
            std::vector<int> segment;
            long long dist = DjkstraWithPath(from, to, graph, segment);
            if (dist == LLONG_MAX) {
                valid = false;
                break;
            }
            totalDist += dist;
            fullPath.insert(fullPath.end(), segment.begin(), segment.end());
        }

        if (valid && totalDist < bestTotal) {
            bestTotal = totalDist;
            bestFullPath = fullPath;
        }

    } while (std::next_permutation(orders.begin(), orders.end()));

    std::cout << bestFullPath.size() << '\n';
    for (size_t i = 0; i < bestFullPath.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << bestFullPath[i] + 1;
    }
    std::cout << '\n';

    return 0;
}