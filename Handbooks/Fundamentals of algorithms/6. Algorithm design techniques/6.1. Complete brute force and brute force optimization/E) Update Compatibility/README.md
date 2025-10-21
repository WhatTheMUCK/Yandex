# Совместимость обновления

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

У вас есть $N$ серверов и $P$ клиентов. Необходимо выбрать ровно $K$ серверов для обновления.  
Для каждого клиента известен список серверов, с которыми он совместим.  
Нужно проверить, можно ли выбрать $K$ серверов так, чтобы **каждый клиент был совместим хотя бы с одним из них**.

Если решения нет, выведите `No solutions`.

## Формат входных данных

- Первая строка: три целых числа $N, P, K$ ($1 \leq K \leq N \leq 22$, $1 \leq P \leq 30$).
- Вторая строка: $N$ целых чисел $w_1, w_2, \dots, w_N$ — задержки серверов ($0 \leq w_i \leq 10^6$).
- Далее $P$ строк. В каждой строке:
  - число $t_j$ — сколько серверов совместимо с клиентом $j$,
  - затем $t_j$ различных индексов серверов от $1$ до $N$.

## Формат выходных данных

Если решение существует:
- первая строка: **минимальная суммарная задержка** выбранных серверов;
- вторая строка: $K$ индексов выбранных серверов **в порядке возрастания**.

Если решений нет: одна строка `No solutions`.

## Примеры

### Пример 1

**Ввод:**
```
4 3 2
2 5 3 4
2 1 2
2 2 3
2 3 4
```

**Вывод:**
```
5
1 3
```

### Пример 2

**Ввод:**
```
3 2 1
1 2 3
1 1
1 2
```

**Вывод:**
```
No solutions
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <limits>

int main() {
    int N, P, K;
    std::cin >> N >> P >> K;
    std::vector<int> w(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> w[i];
    }

    std::unordered_map<int, std::unordered_set<int>> connectivity;
    for (int i = 0; i < P; ++i) {
        int t;
        std::cin >> t;
        for (int j = 0; j < t; ++j) {
            int serverId;
            std::cin >> serverId;
            connectivity[i].insert(serverId - 1);
        }
    }

    std::vector<bool> mask(N, false);
    std::fill(mask.end() - K, mask.end(), true);
    long long minWaiting = std::numeric_limits<long long>::max();
    std::vector<int> bestServers;
    do {
        std::vector<bool> visited(N, false);
        std::vector<int> tempServers;
        int curWaiting = 0;
        for (int i = 0; i < N; ++i) {
            if (mask[i] == false) {
                continue;
            }

            tempServers.push_back(i);
            curWaiting += w[i];

            for (int j = 0; j < P; ++j) {
                if (visited[j]) {
                    continue;
                }

                if (connectivity[j].contains(i)) {
                    visited[j] = true;
                }
            }
        }

        int amountOfConnectedPeople = std::accumulate(visited.begin(), visited.end(), 0);
        if (amountOfConnectedPeople == P && curWaiting < minWaiting) {
            minWaiting = curWaiting;
            bestServers = tempServers;
        }
    } while(std::next_permutation(mask.begin(), mask.end()));

    if (bestServers.empty()) {
        std::cout << "No solutions\n";
    } else {
        std::cout << minWaiting << '\n';
        for (size_t i = 0; i < bestServers.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << bestServers[i] + 1;
        }
        std::cout << '\n';
    }

    return 0;
}
```
