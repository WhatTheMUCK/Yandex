# Ханойские башни

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Головоломка **"Ханойские башни"** состоит из трёх стержней, пронумеруем их слева направо: **1**, **2** и **3**. Также в головоломке используется стопка дисков с отверстием посередине. Радиус дисков уменьшается снизу вверх.

Изначально диски расположены на левом стержне (**стержень 1**), самый большой диск находится внизу.  
Диски в игре перемещаются **по одному** со стержня на стержень.  
Диск можно надеть на стержень, **только если он пустой или верхний диск на нём большего размера**, чем перемещаемый.  

Цель головоломки — перенести все диски со стержня **1** на стержень **3**.

Требуется найти последовательность ходов, которая решает головоломку.

## Формат ввода

В первой строке задано одно число $n$ ($3 \leq n \leq 10$) — количество дисков на первой башне.

## Формат вывода

- В первой строке выведите количество операций $k$.
- В следующих $k$ строках выведите по два числа в каждой: $x_i, y_i$ ($1 \leq x_i, y_i \leq 3$) — переместить верхний диск со стержня $x_i$ на стержень $y_i$.

## Примеры

### Пример 1

**Ввод:**
```
3
```

**Вывод:**
```
7
1 3
1 2
3 2
1 3
2 1
2 3
1 3
```

### Пример 2

**Ввод:**
```
4
```

**Вывод:**
```
15
1 2
1 3
2 3
1 2
3 1
3 2
1 2
1 3
2 3
2 1
3 1
2 3
1 2
1 3
2 3
```

### Пример 3

**Ввод:**
```
5
```

**Вывод:**
```
31
1 3
1 2
3 2
1 3
2 1
2 3
1 3
1 2
3 2
3 1
2 1
3 2
1 3
1 2
3 2
1 3
2 1
2 3
1 3
2 1
3 2
3 1
2 1
2 3
1 3
1 2
3 2
1 3
2 1
2 3
1 3
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <functional>

struct HanoiTowersState {
    int remainded;
    int fromPillar;
    int toPillar;

    bool operator==(const HanoiTowersState & other) const {
        return remainded == other.remainded &&
               fromPillar == other.fromPillar &&
               toPillar == other.toPillar;
    }
};

namespace std {
    template<>
    struct hash<HanoiTowersState> {
        size_t operator()(const HanoiTowersState & s) const {
            return hash<int>()(s.remainded) ^
                   (hash<int>()(s.fromPillar) << 1) ^
                   (hash<int>()(s.toPillar) << 2);
        }
    };
}

std::unordered_map<HanoiTowersState, std::vector<std::pair<int, int>>> states;

std::vector<std::pair<int, int>> HanoiTowers(int n, int fromPillar, int toPillar) {
    HanoiTowersState cur = {n, fromPillar, toPillar};
    if (states.contains(cur)) {
        return states[cur];
    }
    
    if (n == 1) {
        states[cur] = {{fromPillar, toPillar}};
        return states[cur];
    }

    int intermediatePillar = 6 - fromPillar - toPillar;
    states[cur] = HanoiTowers(n - 1, fromPillar, intermediatePillar);
    states[cur].push_back({fromPillar, toPillar});
    std::vector<std::pair<int, int>> temp = HanoiTowers(n - 1, intermediatePillar, toPillar);
    for (const std::pair<int, int> & step : temp) {
        states[cur].push_back(step);
    }
    return states[cur];
}   

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> answer = HanoiTowers(n, 1, 3);
    std::cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i].first << ' ' << answer[i].second << '\n';
    }
    return 0;
}
```
