# Самый безопасный маршрут

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В подземелье есть $n$ уровней и $m$ коридоров между ними. Для каждого коридора известно, что при прохождении через него придётся сразиться с некоторым количеством монстров.

Нужно добраться с уровня $X$ на уровень $Y$, выбрав маршрут с **наименьшим суммарным количеством монстров**.

## Формат входных данных

- Первая строка содержит три целых числа $n$, $m$, $q$ — число уровней, число коридоров и число запросов.  
  ($1 \leq n \leq 2 \cdot 10^3$, $0 \leq m \leq 2 \cdot 10^3$, $1 \leq q \leq 10^3$).
- Далее следуют $m$ строк, каждая содержит три числа $u$, $v$, $w$:  
  - $u$, $v$ — соединённые уровни ($1 \leq u, v \leq n$, $u \ne v$),  
  - $w$ — число монстров на коридоре ($0 \leq w \leq 10^9$).  
  Коридоры двусторонние. Между одной парой уровней может быть несколько коридоров.
- Далее идут $q$ строк запросов: по два числа $X$, $Y$ ($1 \leq X, Y \leq n$) — стартовый и целевой уровни.

## Формат выходных данных

Для каждого запроса выведите в отдельной строке одно число — минимальное суммарное количество монстров на пути из $X$ в $Y$.  
Если добраться невозможно, выведите `-1`.

## Примеры

### Пример 1

**Ввод**  
```
5 6 3
1 5 100
2 3 1
1 2 5
3 5 7
4 5 3
2 4 2
1 3
1 5
2 2
```

**Вывод**  
```
6
10
0
```

### Пример 2

**Ввод**  
```
4 4 2
3 4 5
1 4 100
2 3 4
1 2 3
1 4
2 4
```

**Вывод**  
```
12
9
```
## Решение

main.cpp
```cpp
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
```
