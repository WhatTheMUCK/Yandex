#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <tuple>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, K;
    cin >> n >> m >> K;

    vector<vector<pair<int, int>>> graph(n); 
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        graph[u].emplace_back(v, w);
        graph[v].emplace_back(u, w);
    }

    int X, Y;
    cin >> X >> Y;
    --X; --Y;

    if (X == Y && K == 0) {
        std::cout << "1\n" << X + 1 << "\n";
        return 0;
    }

    vector<unordered_map<int, pair<int, int>>> parent(n);

    using State = pair<int, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    pq.emplace(0, X);
    parent[X][0] = {-1, -1}; 

    int answer_cost = -1;

    long long best_cost = K + 200001;
    while (!pq.empty()) {
        auto [cost, v] = pq.top();
        pq.pop();

        if (parent[v].find(cost) == parent[v].end()) continue;

        if (v == Y && cost >= K) {
            answer_cost = cost;
            break;
        }

        for (auto [u, w] : graph[v]) {
            int new_cost = cost + w;

            if (new_cost > best_cost) continue;

            if (parent[u].find(new_cost) == parent[u].end()) {
                parent[u][new_cost] = {v, cost};
                pq.emplace(new_cost, u);

                if (u == Y && new_cost >= K && new_cost < best_cost) {
                    best_cost = new_cost;
                }
            }
        }
    }

    if (answer_cost == -1) {
        cout << "-1\n";
        return 0;
    }

    vector<int> path;
    int cur_v = Y;
    int cur_c = answer_cost;
    while (cur_v != -1) {
        path.push_back(cur_v);
        auto [prev_v, prev_c] = parent[cur_v][cur_c];
        cur_v = prev_v;
        cur_c = prev_c;
    }
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (int i = 0; i < (int)path.size(); ++i) {
        if (i > 0) cout << " ";
        cout << path[i] + 1;
    }
    cout << "\n";

    return 0;
}