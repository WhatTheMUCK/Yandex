# Склад

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В стране есть $n$ городов и $m$ двусторонних дорог между ними. Компания хочет открыть один центральный склад так, чтобы из него можно было доставить посылку в любой город.

Определите, возможно ли это.

## Формат входных данных

- В первой строке заданы два числа $n$ и $m$ ($1 \leq n \leq 2 \cdot 10^5$, $0 \leq m \leq 2 \cdot 10^5$) — количество городов и количество дорог.
- Далее следуют $m$ строк, каждая содержит по два числа $u$ и $v$ ($1 \leq u, v \leq n$, $u \ne v$) — дорога между городами $u$ и $v$.  
  Между парой городов может быть несколько дорог.

## Формат выходных данных

Выведите `YES`, если можно выбрать город для склада так, чтобы доставка была возможна во все города. Иначе выведите `NO`.

## Примеры

### Пример 1

**Ввод**  
```
5 4
3 5
2 4
2 3
1 2
```

**Вывод**  
```
YES
```

### Пример 2

**Ввод**  
```
4 2
1 2
3 4
```

**Вывод**  
```
NO
```
## Решение

main.cpp
```cpp
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
```
