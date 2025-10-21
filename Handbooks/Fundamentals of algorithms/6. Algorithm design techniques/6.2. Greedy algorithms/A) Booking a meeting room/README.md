# Бронирование переговорки

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Задано $n$ интервалов. Требуется найти **максимальное количество взаимно непересекающихся интервалов**.

Два интервала пересекаются, если они имеют хотя бы одну общую точку.

## Формат ввода

- В первой строке задано одно число $n$ ($1 \leq n \leq 100$) — количество интервалов.
- В следующих $n$ строках заданы интервалы $l_i, r_i$ ($1 \leq l_i \leq r_i \leq 50$).

## Формат вывода

Выведите ответ на задачу.

## Примеры

### Пример 1

**Ввод:**
```
3
1 3
2 3
4 5
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
5
1 2
2 3
4 5
4 5
5 6
```

**Вывод:**
```
2
```

### Пример 3

**Ввод:**
```
2
1 50
49 50
```

**Вывод:**
```
1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, typename V>
std::istream & operator>>(std::istream & is, std::pair<T, V> & rhs) {
    return is >> rhs.first >> rhs.second;
} 

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> timings(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> timings[i];
    }

    std::sort(timings.begin(), timings.end(), [](const auto & lhs, const auto & rhs) {
        return std::tie(lhs.second, lhs.first) < std::tie(rhs.second, rhs.first);
    });

    int answer = 0;
    int r = 0;
    for (int i = 0; i < n; ++i) {
        auto [l1, r1] = timings[i];
        if (l1 > r) {
            ++answer;
            r = r1;
        }
    }

    std::cout << answer << '\n';
    return 0;
}
```
