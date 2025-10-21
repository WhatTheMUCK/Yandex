# Маршрут для фарма

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В подземелье есть $n$ уровней и $m$ коридоров между ними. Для каждого коридора известно, что при прохождении через него придётся сразиться с некоторым количеством монстров. Поскольку подземелье волшебное, при **повторном прохождении** коридора сражаться придётся **заново**.

Герой хочет пройти из уровня $X$ на уровень $Y$, при этом он **обязан сразиться как минимум с $K$ монстрами**.  
Среди всех маршрутов, удовлетворяющих этому условию, нужно выбрать тот, в котором **суммарное количество монстров минимально**.

Требуется найти такой маршрут и вывести последовательность уровней, через которые ему придётся пройти.

## Формат входных данных

- В первой строке заданы три числа $n$, $m$, $K$:  
  ($1 \leq n \leq 10^3$, $0 \leq m \leq 2 \cdot 10^3$, $0 \leq K \leq 10^5$).
- Далее следуют $m$ строк, каждая содержит три числа $u$, $v$, $w$:  
  - $u$, $v$ — соединённые уровни ($1 \leq u, v \leq n$, $u \ne v$),  
  - $w$ — количество монстров на коридоре ($0 \leq w \leq 10^4$).  
  Коридоры двусторонние. Между одной парой уровней может быть несколько коридоров.
- Последняя строка содержит два числа $X$, $Y$ ($1 \leq X, Y \leq n$) — стартовый и целевой уровни.

## Формат выходных данных

- Если маршрут существует, выведите:
  - В первой строке — число $L$ — количество уровней в пути.
  - Во второй строке — $L$ чисел: последовательность уровней от $X$ до $Y$.
- Если такого маршрута не существует, выведите:  
  ```
  -1
  ```

## Примеры

### Пример 1

**Ввод**  
```
5 6 11
2 4 2
4 5 3
3 5 7
1 2 5
1 5 100
2 3 1
1 5
```

**Вывод**  
```
6
1 2 3 2 4 5
```

### Пример 2

**Ввод**  
```
4 4 6
2 3 4
3 4 5
1 4 100
1 2 3
1 4
```

**Вывод**  
```
4
1 2 3 4
```
## Решение

main.cpp
```cpp
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
```
