# Маршрут курьера: кикшеринг

**Ограничение времени:** 2 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан взвешенный, неориентированный, связный граф, состоящий из $n$ вершин и $m$ рёбер.  
Гарантируется, что в графе нет кратных рёбер.

Требуется построить **оптимальный маршрут** от вершины-склада $V$ до всех трёх вершин-заказов $O_1, O_2, O_3$ и обратно в склад $V$.  
Гарантируется, что $V, O_1, O_2, O_3$ попарно различны.

Маршрут должен иметь вид:  
$$
V \rightarrow \dots \rightarrow O_i \rightarrow \dots \rightarrow O_j \rightarrow \dots \rightarrow O_k \rightarrow \dots \rightarrow V,
$$  
где $\{i, j, k\} = \{1, 2, 3\}$ — некоторая перестановка заказов.

### Особенности передвижения

- В графе есть $k$ **станций**. На любой станции можно **арендовать** неограниченное число самокатов.
- В графе есть $l$ **парковок**. Самокат можно **оставить только на парковке**.
- При движении **на самокате** вес ребра уменьшается до $\left\lceil \dfrac{c_i}{2} \right\rceil$.
- При **первом посещении** любой вершины-заказа ($O_1$, $O_2$ или $O_3$) **аренда самоката обрывается** (самокат исчезает).  
  Это не мешает арендовать новый самокат в этой же вершине, если она также является станцией.

Цель — найти маршрут **минимальной общей стоимости** с учётом всех правил.

## Формат ввода

- В первой строке:  
  $n$, $m$, $V$, $O_1$, $O_2$, $O_3$
- Следующие $m$ строк:  
  ```
  u_i v_i c_i
  ```
- Затем число $k$, и строка из $k$ номеров станций $s_i$
- Затем число $l$, и строка из $l$ номеров парковок $p_i$

## Формат вывода

- В первой строке: число $cnt$ — количество вершин в оптимальном пути.
- Во второй строке: сам путь — последовательность номеров вершин.
- В третьей строке: строка из $cnt$ символов:
  - `1`, если на соответствующем **шаге** (то есть при переходе *из* этой вершины) у вас был самокат,
  - `0` — иначе.

> **Примечание:** длина строки в третьей строке равна количеству вершин в пути, но интерпретируется как состояние **до/во время** каждого перехода. Последняя вершина — конечная, самокат после неё не используется.

## Пример

**Ввод**  
```
10 15 5 7 4 2
2 1 754
3 2 1892
4 2 3404
5 3 9972
6 3 2167
7 6 6688
8 6 4848
9 7 7683
10 2 8597
5 7 3202
8 4 8341
4 6 4958
7 3 1030
5 2 2082
3 9 470
3
5 1 2
6
5 1 7 2 6 10
```

**Вывод**  
```
7
5 7 3 2 4 2 5
1001011
```

## Ограничения

- $4 \leq n \leq 10^5$
- $n - 1 \leq m \leq 10^5$
- $1 \leq V, O_1, O_2, O_3 \leq n$
- $1 \leq u_i, v_i \leq n$ для всех $i$
- $1 \leq c_i \leq 10^4$ для всех $i$
- $1 \leq k \leq n$, $1 \leq s_i \leq n$
- $1 \leq l \leq n$, $1 \leq p_i \leq n$
## Решение

main.cpp
```cpp
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
```
