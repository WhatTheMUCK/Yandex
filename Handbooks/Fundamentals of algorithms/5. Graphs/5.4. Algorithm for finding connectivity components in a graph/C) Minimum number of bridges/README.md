# Минимальное количество мостов

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В Байтландии есть $n$ островов и $m$ мостов. Мост не может начинаться и заканчиваться на одном острове.

Вам требуется найти **минимальное количество мостов**, которые нужно построить, чтобы можно было добраться из любого острова в любой другой остров.

## Формат ввода

- В первой строке находятся два числа $n$, $m$ — количество островов и уже существующих мостов.
- В следующих $m$ строках заданы мосты в формате:  
  ```
  u_i v_i
  ```

## Формат вывода

- В первой строке выведите число $k$ — минимальное количество мостов, которые нужно построить.
- В следующих $k$ строках выведите новые мосты в формате:  
  ```
  u v
  ```

Порядок вывода мостов может быть произвольным. Достаточно вывести **любой** корректный набор мостов минимального размера.

## Примеры

### Пример 1

**Ввод**  
```
5 3
1 2
2 4
3 5
```

**Вывод**  
```
1
3 2
```

### Пример 2

**Ввод**  
```
4 3
1 2
2 3
1 3
```

**Вывод**  
```
1
4 3
```

### Пример 3

**Ввод**  
```
2 1
1 2
```

**Вывод**  
```
0
```

## Ограничения

- $1 \leq n, m \leq 10^5$
- $1 \leq u_i, v_i \leq n$ для всех $i$ от $1$ до $m$
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

    }
    std::cout << components.size() - static_cast<size_t>(1) << '\n';
    for (size_t i = 1; i < components.size(); ++i) {
        std::cout << components[i - 1][0] + 1 << ' ' << components[i][0] + 1 << '\n';
    }

    return 0;
}
```
