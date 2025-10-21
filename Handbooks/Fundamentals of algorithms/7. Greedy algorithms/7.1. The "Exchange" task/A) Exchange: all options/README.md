# Размен: все варианты

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Предположим, что у кассира есть **бесконечное количество монет** номиналами **1**, **5**, **10**.

Найдите **все наборы монет**, которые в сумме дают `money`.  
Требуется вывести **количество подходящих наборов** и **сами наборы**.

> Два набора считаются **различными**, если **мульти-множества монет не совпадают** (то есть порядок не важен, но количество каждой монеты — важно).

## Формат ввода

Целое число `money` ($1 \leq \text{money} \leq 1000$).

## Формат вывода

- В первой строке выведите количество наборов $m$.
- В следующих $m$ строках выведите сами наборы в формате:  
  сначала — **общее количество монет в наборе**,  
  затем — **номиналы всех монет** через пробел (в любом порядке).

> Наборы можно выводить в **любом порядке**.

## Примеры

### Пример 1

**Ввод:**
```
10
```

**Вывод:**
```
4
1 10
2 5 5
6 1 1 1 1 1 5
10 1 1 1 1 1 1 1 1 1 1
```

### Пример 2

**Ввод:**
```
1
```

**Вывод:**
```
1
1 1
```

### Пример 3

**Ввод:**
```
5
```

**Вывод:**
```
2
1 5
5 1 1 1 1 1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int money;
    std::cin >> money;

    std::vector<std::vector<int>> solutions;

    for (int cnt10 = 0; cnt10 <= money / 10; ++cnt10) {
        int remaining_after_10 = money - cnt10 * 10;
        for (int cnt5 = 0; cnt5 <= remaining_after_10 / 5; ++cnt5) {
            int remaining = remaining_after_10 - cnt5 * 5;
            int cnt1 = remaining;

            std::vector<int> set;
            set.push_back(cnt1 + cnt5 + cnt10);

            for (int i = 0; i < cnt10; ++i) set.push_back(10);
            for (int i = 0; i < cnt5; ++i) set.push_back(5);
            for (int i = 0; i < cnt1; ++i) set.push_back(1);

            solutions.push_back(set);
        }
    }

    std::cout << solutions.size() << '\n';
    for (const auto& sol : solutions) {
        for (size_t i = 0; i < sol.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << sol[i];
        }
        std::cout << '\n';
    }

    return 0;
}
```
