# Рейтинг в шахматном турнире

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Даны $m$ партий в шахматном турнире. В каждой известен победитель. Требуется определить, возможно ли однозначно определить уровень игрока.

Будем считать, что у каждого игрока есть свой уникальный скрытый уровень. Игрок с большим уровнем всегда побеждает игрока с меньшим уровнем.

## Формат ввода

- В первой строке заданы два числа $n$, $m$ — количество участников турнира и количество партий.
- В следующих $m$ строках заданы партии в формате:  
  ```
  u_i v_i t_i
  ```  
  где $u_i$, $v_i$ — номера игроков, а $t_i$ — победитель:  
  - $t_i = 1$ означает, что победил игрок $u_i$,  
  - $t_i = 2$ означает, что победил игрок $v_i$.

## Формат вывода

В единственной строке вывести `YES`, если однозначно можно определить уровень всех игроков, и `NO` иначе.

## Примеры

### Пример 1

**Ввод**  
```
5 6
1 4 1
1 2 1
3 1 2
4 2 1
2 3 1
5 3 2
```

**Вывод**  
```
YES
```

### Пример 2

**Ввод**  
```
5 1
1 3 1
```

**Вывод**  
```
NO
```

### Пример 3

**Ввод**  
```
5 2
2 4 2
3 2 1
```

**Вывод**  
```
NO
```

## Ограничения

- $1 \leq n, m \leq 10^5$
- $1 \leq u_i, v_i \leq n$ для всех $i$ от $1$ до $m$
- $1 \leq t_i \leq 2$ для всех $i$ от $1$ до $m$
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj(n);
    std::vector<int> inputDegree(n, 0);

    for (int i = 0; i < m; ++i) {
        int u, v, t;
        std::cin >> u >> v >> t;
        --u, --v;

        if (t == 1) {
            adj[u].push_back(v);
            ++inputDegree[v];
        } else {
            adj[v].push_back(u);
            ++inputDegree[u];
        }
    }

    std::queue<int> BFS;
    for (int i = 0; i < n; ++i) {
        if (inputDegree[i] == 0) {
            BFS.push(i);
        }
    }

    int processed = 0;
    bool uniqueOrder = true;

    while (!BFS.empty()) {
        if (BFS.size() > 1) {
            uniqueOrder = false;
        }

        int v = BFS.front();
        BFS.pop();
        ++processed;

        for (int to : adj[v]) {
            --inputDegree[to];
            if (inputDegree[to] == 0) {
                BFS.push(to);
            }
        }
    }

    if (processed != n || !uniqueOrder) {
        std::cout << "NO\n";
    } else {
        std::cout << "YES\n";
    }

    return 0;
}
```
