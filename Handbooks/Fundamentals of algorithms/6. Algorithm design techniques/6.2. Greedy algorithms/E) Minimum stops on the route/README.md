# Минимум остановок на маршруте

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Автомобиль движется по прямой из точки $0$ в точку с координатой $L$.  
Расход топлива — $1$ единица на $1$ километр. В начале в баке $F$ единиц топлива.

На маршруте расположены $n$ заправок; $i$-я заправка находится в точке $x_i$ ($0 < x_i < L$) и содержит $a_i$ единиц топлива.  
Объём бака **не ограничен**, заправка происходит **мгновенно**, но на каждой заправке можно забрать **не больше**, чем $a_i$.

Требуется добраться до точки $L$, совершив **минимально возможное число заправок**.  
Если это невозможно, выведите $-1$.

## Формат входных данных

- Первая строка: одно целое число $n$ — количество заправок.
- Вторая строка: два целых числа $L$ и $F$ — координата пункта назначения и начальный объём топлива.
- Следующие $n$ строк: по два целых числа $x_i$ и $a_i$ — координата и доступное топливо на $i$-й заправке.

**Гарантируется:**
- $0 \leq n \leq 2 \cdot 10^5$
- $1 \leq L \leq 10^9$
- $0 \leq F \leq 10^9$
- $1 \leq x_i \leq L - 1$
- $1 \leq a_i \leq 10^9$

Порядок заправок во входных данных **произвольный**.

## Формат выходных данных

Одно целое число — минимальное количество заправок для достижения точки $L$, либо $-1$, если добраться невозможно.

## Примеры

### Пример 1

**Ввод:**
```
4
25 10
10 10
14 5
20 2
21 4
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
3
100 1
10 1
20 1
30 1
```

**Вывод:**
```
-1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    long long L, F;
    std::cin >> L >> F;

    std::vector<std::pair<long long, long long>> stations;
    for (int i = 0; i < n; ++i) {
        long long x, a;
        std::cin >> x >> a;
        stations.emplace_back(x, a);
    }

    stations.emplace_back(L, 0);
    std::sort(stations.begin(), stations.end());

    std::priority_queue<long long> max_heap;

    long long current_fuel = F;
    int refills = 0;
    long long prev_pos = 0;

    for (const auto& [pos, fuel] : stations) {
        long long distance = pos - prev_pos;

        while (current_fuel < distance) {
            if (max_heap.empty()) {
                std::cout << "-1\n";
                return 0;
            }
            current_fuel += max_heap.top();
            max_heap.pop();
            refills++;
        }

        current_fuel -= distance;
        prev_pos = pos;

        if (pos != L) {
            max_heap.push(fuel);
        }
    }

    std::cout << refills << '\n';
    return 0;
}
```
