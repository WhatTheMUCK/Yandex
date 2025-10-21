# Примитивный калькулятор

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

У вас есть калькулятор, который выполняет только следующие операции с целым числом $x$:
- прибавить $1$: $x \to x + 1$,
- умножить на $2$: $x \to 2x$,
- умножить на $3$: $x \to 3x$.

Имея положительное целое число $n$, вы должны найти **минимальное количество операций**, необходимых для получения числа $n$ из числа $1$.

## Формат ввода

Целое число $n$.

**Ограничения:**  
$1 \leq n \leq 10^6$

## Формат вывода

- В **первой строке**: $k$ — минимальное число необходимых операций для получения $n$ из $1$.
- Во **второй строке**: последовательность промежуточных чисел $a_0, a_1, \dots, a_k$, такая что:
  - $a_0 = 1$,
  - $a_k = n$,
  - для каждого $1 \leq i \leq k$ значение $a_i$ получено из $a_{i-1}$ одной из трёх операций:
    - $a_i = a_{i-1} + 1$,
    - $a_i = 2 \cdot a_{i-1}$,
    - $a_i = 3 \cdot a_{i-1}$.

Если таких последовательностей несколько, выведите **любую** из них.

## Примеры

### Пример 1

**Ввод:**
```
5
```

**Вывод:**
```
3
1 3 4 5
```

### Пример 2

**Ввод:**
```
10
```

**Вывод:**
```
3
1 3 9 10
```

### Пример 3

**Ввод:**
```
17
```

**Вывод:**
```
5
1 3 4 8 16 17
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    int infinity = std::numeric_limits<int>::max();
    std::vector<int> dp(n + 1, infinity), parents(n + 1);
    dp[1] = 0;
    parents[1] = 1;
    for (int i = 2; i <= n; ++i) {
        int parent = i - 1;
        dp[i] = std::min(dp[i], dp[i - 1] + 1);
        if (i % 2 == 0 && dp[i / 2] + 1 < dp[i]) {
            parent = i / 2;
            dp[i] = dp[i / 2] + 1;
        }

        if (i % 3 == 0 && dp[i / 3] + 1 < dp[i]) {
            parent = i / 3;
            dp[i] = dp[i / 3] + 1;
        }

        parents[i] = parent;
    }

    std::cout << dp[n] << '\n';
    std::vector<int> answer;
    int curIndex = n;
    while (curIndex != parents[curIndex]) {
        answer.push_back(curIndex);
        curIndex = parents[curIndex];
    }
    answer.push_back(1);
    std::reverse(answer.begin(), answer.end());
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}
```
