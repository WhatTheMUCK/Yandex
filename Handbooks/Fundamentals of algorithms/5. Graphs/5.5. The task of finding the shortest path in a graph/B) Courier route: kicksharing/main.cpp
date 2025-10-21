#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

const long long INF = LLONG_MAX;

struct State {
    int v;
    bool scooter;
    int mask;
    long long dist;

    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

struct ParentInfo {
    int from_v;
    bool from_scooter;
    int from_mask;
    bool scooter_used;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, V, O1, O2, O3;
    cin >> n >> m >> V >> O1 >> O2 >> O3;
    V--; O1--; O2--; O3--;

    vector<vector<pair<int, int>>> graph(n);
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        u--; v--;
        graph[u].emplace_back(v, c);
        graph[v].emplace_back(u, c);
    }

    vector<bool> isStation(n, false);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int s; cin >> s; s--;
        isStation[s] = true;
    }

    vector<bool> isParking(n, false);
    int l;
    cin >> l;
    for (int i = 0; i < l; ++i) {
        int p; cin >> p; p--;
        isParking[p] = true;
    }

    vector<int> orderIndex(n, -1);
    orderIndex[O1] = 0;
    orderIndex[O2] = 1;
    orderIndex[O3] = 2;
    vector<int> orders = {O1, O2, O3};

    vector<int> bestPath;
    string bestScooterStr;
    long long bestDist = INF;

    sort(orders.begin(), orders.end());
    do {
        vector<vector<vector<long long>>> dist(n, vector<vector<long long>>(2, vector<long long>(8, INF)));
        vector<vector<vector<ParentInfo>>> parent(n, vector<vector<ParentInfo>>(2, vector<ParentInfo>(8, {-1, false, -1, false})));

        priority_queue<State, vector<State>, greater<>> pq;

        dist[V][0][0] = 0;
        pq.push({V, false, 0, 0});
        if (isStation[V]) {
            dist[V][1][0] = 0;
            pq.push({V, true, 0, 0});
        }

        State finalState{-1, false, -1, INF};
        bool found = false;

        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            if (cur.dist != dist[cur.v][cur.scooter][cur.mask]) continue;

            if (cur.v == V && cur.mask == 7) {
                finalState = cur;
                found = true;
                break;
            }

            for (auto [to, cost] : graph[cur.v]) {
                long long edgeCost = cur.scooter ? (cost + 1) / 2 : cost;
                bool newScooter = cur.scooter;
                int newMask = cur.mask;

                if (orderIndex[to] != -1) {
                    int bit = orderIndex[to];
                    if (!(cur.mask & (1 << bit))) {
                        newScooter = false;
                        newMask |= (1 << bit);
                    }
                }

                if (cur.dist + edgeCost < dist[to][newScooter][newMask]) {
                    dist[to][newScooter][newMask] = cur.dist + edgeCost;
                    parent[to][newScooter][newMask] = {cur.v, cur.scooter, cur.mask, cur.scooter};
                    pq.push({to, newScooter, newMask, cur.dist + edgeCost});
                }
            }

            if (!cur.scooter && isStation[cur.v]) {
                if (cur.dist < dist[cur.v][1][cur.mask]) {
                    dist[cur.v][1][cur.mask] = cur.dist;
                    parent[cur.v][1][cur.mask] = {cur.v, cur.scooter, cur.mask, false};
                    pq.push({cur.v, true, cur.mask, cur.dist});
                }
            }
            if (cur.scooter && isParking[cur.v]) {
                if (cur.dist < dist[cur.v][0][cur.mask]) {
                    dist[cur.v][0][cur.mask] = cur.dist;
                    parent[cur.v][0][cur.mask] = {cur.v, cur.scooter, cur.mask, false};
                    pq.push({cur.v, false, cur.mask, cur.dist});
                }
            }
        }

        if (!found) continue;

        vector<int> path;
        string scooterStr;

        int cv = V, cs = finalState.scooter, cm = 7;

        while (true) {
            auto p = parent[cv][cs][cm];
            if (p.from_v == -1) break;

            if (p.from_v == cv) {
                cs = p.from_scooter;
                cm = p.from_mask;
                continue;
            }

            path.push_back(cv);
            scooterStr.push_back(p.scooter_used ? '1' : '0');

            cv = p.from_v;
            cs = p.from_scooter;
            cm = p.from_mask;

            if (cv == V && cm == 0) {
                path.push_back(cv);
                break;
            }
        }

        reverse(path.begin(), path.end());
        reverse(scooterStr.begin(), scooterStr.end());

        if (!scooterStr.empty()) {
            scooterStr += scooterStr.back();
        } else {
            scooterStr += '0';
        }

        if (dist[V][finalState.scooter][7] < bestDist) {
            bestDist = dist[V][finalState.scooter][7];
            bestPath = path;
            bestScooterStr = scooterStr;
        }

    } while (next_permutation(orders.begin(), orders.end()));

    cout << bestPath.size() << '\n';
    for (int i = 0; i < (int)bestPath.size(); ++i) {
        if (i) cout << ' ';
        cout << bestPath[i] + 1;
    }
    cout << '\n';
    cout << bestScooterStr << '\n';

    return 0;
}