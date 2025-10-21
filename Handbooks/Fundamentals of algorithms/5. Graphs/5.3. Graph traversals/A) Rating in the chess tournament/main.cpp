#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> inputDegree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, t;
        std::cin >> u >> v >> t;
        --u, --v;

        if (t == 1) {
            adj[u].push_back(v);
            ++inputDegree[v];
        } else {
            adj[v].push_back(u);
            ++inputDegree[u];
        }
    }

    std::queue<int> BFS;
    for (int i = 0; i < n; ++i) {
        if (inputDegree[i] == 0) {
            BFS.push(i);
        }
    }

    int processed = 0;
    bool uniqueOrder = true;

    while (!BFS.empty()) {
        if (BFS.size() > 1) {
            uniqueOrder = false;
        }

        int v = BFS.front();
        BFS.pop();
        ++processed;

        for (int to : adj[v]) {
            --inputDegree[to];
            if (inputDegree[to] == 0) {
                BFS.push(to);
            }
        }
    }

    if (processed != n || !uniqueOrder) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }

    return 0;
}