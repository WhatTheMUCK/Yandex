# Количество пар с суммой не больше S

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив из $n$ целых чисел $a_1, a_2, \dots, a_n$ и число $S$.  
Требуется посчитать количество пар индексов $(i, j)$, таких что:

- $1 \leq i < j \leq n$
- $a_i + a_j \leq S$

## Формат входных данных

- Первая строка содержит два целых числа $n$ и $S$  
  ($1 \leq n \leq 2 \cdot 10^5$, $|S| \leq 10^{12}$).
- Вторая строка содержит $n$ целых чисел $a_i$  
  ($|a_i| \leq 10^9$).

## Формат выходных данных

Выведите одно число — количество пар $(i, j)$, удовлетворяющих условию.

## Примеры

### Пример 1

**Ввод:**
```
5 4
1 2 3 0 -1
```

**Вывод:**
```
9
```

### Пример 2

**Ввод:**
```
6 0
-1 -1 1 1 0 0
```

**Вывод:**
```
10
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    long long n, S;
    std::cin >> n >> S;
    std::vector<long long> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        int endIndex = std::upper_bound(vec.begin() + i + 1, vec.end(), S - vec[i]) - vec.begin() - 1;
        if (endIndex == i) {
            break;
        }
        answer += endIndex - i;
    }

    std::cout << answer << '\n';
    
    return 0;
}
```
