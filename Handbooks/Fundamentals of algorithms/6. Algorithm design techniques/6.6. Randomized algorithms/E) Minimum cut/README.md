# Минимальный разрез

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В неориентированном графе с $n$ вершинами и $m$ рёбрами требуется найти **минимальный разрез**.

**Разрезом** называется разделение множества вершин на две **непересекающиеся непустые** части.  
**Вес разреза** равен количеству рёбер, которые соединяют вершины из **разных частей**.  
**Минимальный разрез** — это разрез с **минимальным весом**.

## Формат входных данных

- Первая строка содержит два целых числа $n$ и $m$  
  ($2 \leq n \leq 200$, $1 \leq m \leq 2000$) — количество вершин и рёбер.
- Далее следуют $m$ строк, каждая из которых содержит два целых числа $u$ и $v$  
  ($1 \leq u, v \leq n$, $u \ne v$) — описание ребра между вершинами $u$ и $v$.

> Между одной парой вершин может быть **несколько рёбер** (мультиграф).

## Формат выходных данных

Выведите одно целое число — **вес минимального разреза**.

## Примечание

Одним из способов решения этой задачи является **рандомизированный алгоритм Каргера**:

- Пока в графе больше двух вершин:
  - Случайным образом выбирается ребро.
  - Его концы «схлопываются» в одну вершину (объединяются).
  - Кратные рёбра сохраняются.
- Когда остаётся две вершины, число рёбер между ними равно весу разреза.
- Чтобы увеличить вероятность найти **минимальный** разрез, алгоритм запускают **много раз** и выбирают наименьший результат.

## Примеры

### Пример 1

**Ввод:**
```
4 4
1 2
2 3
3 4
4 1
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
5 5
1 2
2 3
3 4
4 5
5 1
```

**Вывод:**
```
2
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

// Глобальный генератор
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int karger(const vector<pair<int, int>>& orig_edges, int n) {
    vector<pair<int, int>> edges = orig_edges;
    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i; // сжатие путей не нужно, просто метки

    int vertices = n;
    while (vertices > 2) {
        // Удалим петли и выберем случайное ребро
        vector<pair<int, int>> clean;
        for (auto [u, v] : edges) {
            int lu = label[u], lv = label[v];
            if (lu != lv) {
                clean.emplace_back(lu, lv);
            }
        }
        edges = move(clean);
        if (edges.empty()) break; // граф несвязный — разрез 0

        // Случайное ребро
        uniform_int_distribution<int> dist(0, (int)edges.size() - 1);
        int idx = dist(rng);
        int u = edges[idx].first;
        int v = edges[idx].second;

        // Стягиваем v в u: все v → u
        for (int i = 0; i < n; ++i) {
            if (label[i] == v) {
                label[i] = u;
            }
        }
        vertices--;
    }

    // Считаем рёбра между двумя оставшимися компонентами
    vector<pair<int, int>> clean;
    for (auto [u, v] : orig_edges) {
        int lu = label[u], lv = label[v];
        if (lu != lv) {
            clean.emplace_back(lu, lv);
        }
    }
    return (int)clean.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges.emplace_back(u, v);
    }

    int best = INT_MAX;
    // Число запусков: ~ n*n*log(n) — но ограничим ради времени
    int trials = min(1000, (int)(n * n * 2)); // для n=200 → 80000, но ограничим

    // Однако 1000 — безопасный выбор
    trials = 1000;

    for (int t = 0; t < trials; ++t) {
        int cut = karger(edges, n);
        if (cut < best) best = cut;
    }

    cout << best << '\n';
    return 0;
}
```
