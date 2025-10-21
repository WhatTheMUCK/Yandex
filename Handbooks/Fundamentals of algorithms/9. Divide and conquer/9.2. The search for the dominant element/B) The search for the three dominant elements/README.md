# Поиск трёх доминирующих элементов

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дана последовательность $a$ из $n$ целых неотрицательных чисел.

Требуется определить, **существуют ли три различных элемента**, каждый из которых встречается **более чем** $\frac{n}{4}$ раз.

Обратите внимание:
- Речь идёт именно о **трёх различных значениях**, удовлетворяющих условию.
- Условие «более $n/4$» означает строгое неравенство: количество вхождений $> \frac{n}{4}$.

## Формат ввода

- Первая строка: целое число $n$ — длина последовательности.  
- Вторая строка: $n$ целых чисел $a_0, a_1, \dots, a_{n-1}$.

**Ограничения:**  
$1 \leq n \leq 10^5$,  
$0 \leq a_i \leq 10^9$ для всех $0 \leq i < n$.

## Формат вывода

Выведите:
- `1`, если в последовательности **существуют три различных элемента**, каждый из которых встречается **более** $\frac{n}{4}$ раз,
- `0` — в противном случае.

## Примеры

### Пример 1

**Ввод:**
```
11
0 9 2 3 9 0 2 9 2 3 3
```

**Вывод:**
```
1
```

### Пример 2

**Ввод:**
```
4
1 2 3 1
```

**Вывод:**
```
0
```

### Пример 3

**Ввод:**
```
3
0 2 1
```

**Вывод:**
```
1
```

### Пример 4

**Ввод:**
```
10
1 2 1 2 1 2 1 2 1 2
```

**Вывод:**
```
0
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::unordered_map<int, int> candidates;

    for (int x : a) {
        if (candidates.count(x)) {
            candidates[x]++;
        }

        else if (static_cast<int>(candidates.size()) < 3) {
            candidates[x] = 1;
        }

        else {
            std::vector<int> toErase;
            for (auto& [key, cnt] : candidates) {
                cnt--;
                if (cnt == 0) {
                    toErase.push_back(key);
                }
            }
            for (int key : toErase) {
                candidates.erase(key);
            }
        }
    }


    std::unordered_map<int, int> freq;
    for (int x : a) {
        if (candidates.count(x)) {
            freq[x]++;
        }
    }

    int count = 0;
    for (auto& [val, f] : freq) {
        if (f > n / 4) {
            count++;
        }
    }

    std::cout << (count >= 3 ? 1 : 0) << '\n';

    return 0;
}
```
