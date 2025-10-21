#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>


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
    std::vector<std::vector<int>> components;
    size_t maxCitiesInComponent = 0;
    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            continue;
        }

        components.push_back({});

        std::queue<int> BFS;
        BFS.push(i);
        visited[i] = true;
        while (!BFS.empty()) {
            int curCity = BFS.front();
            BFS.pop();

            components.back().push_back(curCity);

            for (int neighbour : listOfAdjacency[curCity]) {
                if (visited[neighbour]) {
                    continue;
                }

                visited[neighbour] = true;
                BFS.push(neighbour);
            }
        }

        maxCitiesInComponent = std::max(maxCitiesInComponent, components.back().size());
    }
    std::cout << components.size() << '\n';
    std::cout << maxCitiesInComponent << '\n';

    return 0;
}