#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <numeric>


int main() {
    int n, m;
    std::cin >> n >> m;

    std::unordered_map<int, std::vector<int>> listOfAdjacency;
    for (int i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
        --u, --v;
        listOfAdjacency[u].push_back(v);
        listOfAdjacency[v].push_back(u);
    }

    std::vector<bool> visited(n);
    std::queue<int> BFS;
    BFS.push(0);
    visited[0] = true;
    while (!BFS.empty()) {
        int curCity = BFS.front();
        BFS.pop();

        for (int neighbour : listOfAdjacency[curCity]) {
            if (visited[neighbour]) {
                continue;
            }

            visited[neighbour] = true;
            BFS.push(neighbour);
        }
    }

    bool allConnected = (std::accumulate(visited.begin(), visited.end(), 0) == n);
    std::cout << (allConnected ? "YES" : "NO") << '\n';
    return 0;
}