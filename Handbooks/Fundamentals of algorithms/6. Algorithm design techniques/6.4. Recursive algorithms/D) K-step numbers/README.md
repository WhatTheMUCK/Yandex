# K-ступенчатые числа

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Назовём число **$K$-ступенчатым**, если для любых соседних цифр $a_i$ и $a_{i+1}$ выполняется:

$$
|a_i - a_{i+1}| = K
$$

Сгенерируйте **все** $K$-ступенчатые числа длины $N$.

> Числа **не должны иметь ведущих нулей**, то есть первая цифра должна быть от 1 до 9.

## Формат входных данных

Дана одна строка, содержащая два целых числа $N$ и $K$:
- $1 \leq N \leq 15$
- $0 \leq K \leq 9$

## Формат выходных данных

Все $N$-значные $K$-ступенчатые числа, по одному в строке, в **произвольном порядке**.

## Примеры

### Пример 1

**Ввод:**
```
3 0
```

**Вывод:**
```
111
222
333
444
555
666
777
888
999
```

### Пример 2

**Ввод:**
```
5 5
```

**Вывод:**
```
16161
27272
38383
49494
50505
61616
72727
83838
94949
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_set>

std::unordered_set<long long> visited;

void generate(long long number, int diff, int curLen, int n) {
    if (visited.contains(number)) {
        return;
    }

    visited.insert(number);

    if (curLen == n) {
        std::cout << number << '\n';
        return;
    }

    int lastDigit = number % 10;
    if (lastDigit + diff <= 9) {
        generate(10 * number + (lastDigit + diff), diff, curLen + 1, n);
    }

    if (lastDigit - diff >= 0) {
        generate(10 * number + (lastDigit - diff), diff, curLen + 1, n);
    }
    return;
}

int main() {
    long long n, k;
    std::cin >> n >> k;

    for (int i = 1; i < 10; ++i) {
        generate(i, k, 1, n);
    }
    return 0;
}
```
