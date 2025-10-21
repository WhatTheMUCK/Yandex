# Перепад цен

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив `a`, состоящий из `n` чисел. Необходимо найти две пары индексов `i₁ < j₁` и `i₂ < j₂` таких, что:

- `a[i₁] - a[j₁]` — минимально возможное (наименьший перепад),
- `a[i₂] - a[j₂]` — максимально возможное (наибольший перепад).

## Формат ввода

Первая строка содержит единственное число `n` — количество чисел в массиве.  
Вторая строка содержит `n` целых чисел `a₁, a₂, ..., aₙ`, разделённых пробелами.

## Формат вывода

Первая строка вывода должна содержать два числа `i₁` и `j₁` — индексы (нумерация с 1), соответствующие минимальному значению разности `a[i₁] - a[j₁]`.  
Если таких пар несколько, выбрать ту, у которой:
- минимальное `i₁`;
- при равных `i₁` — минимальное `j₁`.

Вторая строка вывода должна содержать два числа `i₂` и `j₂` — индексы, соответствующие максимальному значению разности `a[i₂] - a[j₂]`.  
Если таких пар несколько, выбрать ту, у которой:
- минимальное `i₂`;
- при равных `i₂` — минимальное `j₂`.

## Пример 1

**Ввод:**
```
6
2 1 3 5 2 4
```

**Вывод:**
```
2 4
4 5
```

## Пример 2

**Ввод:**
```
5
3 2 4 5 6
```

**Вывод:**
```
2 5
1 2
```

## Примечание

**Ограничения:**  
- `3 ≤ n ≤ 10⁵`  
- `1 ≤ aᵢ ≤ 10⁵` для всех `1 ≤ i ≤ n`
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

std::ostream & operator<<(std::ostream & os, std::pair<int, int> rhs) {
    return os << rhs.first << ' ' << rhs.second;
}
int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    int minLeft = vec[0], maxLeft = vec[0];
    int minLeftInd = 0, maxLeftInd = 0;
    int minDiff = vec[0] - vec[1], maxDiff = vec[0] - vec[1];
    std::pair<int, int> minDiffIndices = {0, 1}, maxDiffIndices = {0, 1};
    for (int i = 1; i < n; ++i) {
        int potentialMinDiff = minLeft - vec[i];
        int potentialMaxDiff = maxLeft - vec[i];
        if (minDiff > potentialMinDiff) {
            minDiffIndices = {minLeftInd, i};
            minDiff = potentialMinDiff;
        } 

        if (maxDiff < potentialMaxDiff) {
            maxDiffIndices = {maxLeftInd, i};
            maxDiff = potentialMaxDiff;
        }

        if (minLeft > vec[i]) {
            minLeftInd = i;
            minLeft = vec[i];
        }

        if (maxLeft < vec[i]) {
            maxLeftInd = i;
            maxLeft = vec[i];
        }
    }
    
    ++minDiffIndices.first;
    ++minDiffIndices.second;
    ++maxDiffIndices.first;
    ++maxDiffIndices.second;

    std::cout << minDiffIndices << '\n' << maxDiffIndices << '\n';
    return 0;
}
```
