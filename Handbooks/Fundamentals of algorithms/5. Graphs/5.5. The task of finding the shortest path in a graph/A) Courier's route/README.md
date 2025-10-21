# Маршрут курьера

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан взвешенный, неориентированный, связный граф, состоящий из $n$ вершин и $m$ рёбер.

Гарантируется, что в графе нет кратных рёбер.

Требуется построить **оптимальный маршрут курьера** от вершины-склада $V$ до всех трёх вершин-заказов $O_1, O_2, O_3$ и обратно в склад $V$.

Гарантируется, что $V, O_1, O_2, O_3$ попарно различны.

Маршрут должен иметь вид:  
$$
V \rightarrow \dots \rightarrow O_i \rightarrow \dots \rightarrow O_j \rightarrow \dots \rightarrow O_k \rightarrow \dots \rightarrow V,
$$  
где $\{i, j, k\} = \{1, 2, 3\}$ — некоторая перестановка заказов.

Цель — минимизировать **общую длину пути**.

## Формат ввода

- В первой строке заданы шесть чисел:  
  $n$, $m$, $V$, $O_1$, $O_2$, $O_3$ —  
  количество вершин, количество рёбер, номер склада и номера трёх заказов.
- В следующих $m$ строках заданы рёбра:  
  ```
  u_i v_i c_i
  ```  
  где $u_i$, $v_i$ — концы ребра, $c_i$ — его вес.

## Формат вывода

- В первой строке выведите количество вершин в оптимальном пути.
- Во второй строке выведите сам путь — последовательность номеров вершин.

## Пример

**Ввод**  
```
5 10 3 2 4 5
2 1 3873
3 1 7914
4 2 2158
5 3 6471
1 5 9621
4 1 5954
2 3 4959
4 5 8410
2 5 8420
4 3 4064
```

**Вывод**  
```
5
3 4 2 5 3
```

## Ограничения

- $4 \leq n \leq 10^5$
- $n - 1 \leq m \leq 10^5$
- $1 \leq V, O_1, O_2, O_3 \leq n$
- $1 \leq u_i, v_i \leq n$ для всех $i$
- $1 \leq c_i \leq 10^4$ для всех $i$
## Решение

main.cpp
```cpp
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
```
