# Оптимальный размен

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Задано одно целое число $money$. Требуется представить число $money$ в виде суммы **минимального количества монет** номиналами $1$, $3$ и $4$.

## Формат ввода

Целое число $money$.

**Ограничения:**  
$1 \leq money \leq 10^3$

## Формат вывода

Минимальное количество монет номиналами $1$, $3$, $4$, чтобы получить сумму $money$.

## Примеры

### Пример 1

**Ввод:**
```
18
```

**Вывод:**
```
5
```

### Пример 2

**Ввод:**
```
20
```

**Вывод:**
```
5
```

### Пример 3

**Ввод:**
```
34
```

**Вывод:**
```
9
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <limits>


int main() {
    int money;
    std::cin >> money;
    std::vector<int> nominals = {1, 3, 4};
    int infinity = std::numeric_limits<int>::max();
    std::vector<int> dp(money + 1, infinity);
    dp[0] = 0;
    for (int i = 1; i <= money; ++i) {
        for (int nominal : nominals) {
            if ((i - nominal) < 0) {
                break;
            }
            dp[i] = std::min(dp[i], dp[i - nominal] + 1);
        }
    }
    std::cout << dp[money] << '\n';
    return 0;
}
```
