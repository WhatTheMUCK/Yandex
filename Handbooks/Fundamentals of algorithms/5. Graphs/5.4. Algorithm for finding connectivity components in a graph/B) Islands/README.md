# Острова

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В одном островном государстве расположено $n$ городов и $m$ дорог между ними. Дороги соединяют города попарно и являются двусторонними.

Считается, что города принадлежат одному острову, если из любого города этого множества можно добраться в любой другой город, используя только данные дороги. Такие множества городов будем называть **островами**.

Необходимо определить общее количество островов и найти максимальное количество городов, которое находится на одном острове.

## Формат входных данных

- Первая строка содержит два числа $n$ и $m$ ($1 \leq n \leq 10^3$, $0 \leq m \leq 10^5$) — количество городов и количество дорог.
- Далее следуют $m$ строк, каждая из которых содержит по два числа $u$ и $v$ ($1 \leq u, v \leq n$, $u \ne v$) — описание дороги между городами $u$ и $v$.

Гарантируется, что между каждой парой городов не более одной дороги.

## Формат выходных данных

- В первой строке выведите одно число $k$ — количество островов.
- Во второй строке выведите одно число — максимальный размер острова (число городов в нём).

## Примеры

### Пример 1

**Ввод**  
```
6 3
1 2
5 6
2 3
```

**Вывод**  
```
3
3
```

### Пример 2

**Ввод**  
```
7 5
4 5
1 4
2 3
6 7
1 2
```

**Вывод**  
```
2
5
```
## Решение

main.cpp
```cpp
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
```
