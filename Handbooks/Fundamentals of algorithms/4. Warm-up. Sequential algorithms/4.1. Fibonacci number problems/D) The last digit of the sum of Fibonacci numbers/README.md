# Последняя цифра суммы чисел Фибоначчи

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дано число $n$, необходимо найти **последнюю цифру** суммы  
$$
F_0 + F_1 + F_2 + \dots + F_n,
$$
где $F_i$ — $i$-е число Фибоначчи ($F_0 = 0$, $F_1 = 1$, $F_{i} = F_{i-1} + F_{i-2}$ при $i \geq 2$).

## Формат ввода

Целое число $n$.

**Ограничения:**  
$$
0 \leq n \leq 10^{14}
$$

## Формат вывода

Последняя цифра суммы $F_0 + F_1 + F_2 + \dots + F_n$.

## Примеры

### Пример 1

**Ввод**
```
3
```

**Вывод**
```
4
```
---

### Пример 2

**Ввод**
```
100
```

**Вывод**
```
5
```

## Примечание

Исчерпывающий поиск будет слишком медленным для этой задачи. Попробуйте придумать **формулу** для суммы:
$$
S(n) = F_0 + F_1 + \dots + F_n.
$$
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

typedef std::vector<std::vector<long long>> matrix;
typedef std::vector<long long> row;

std::ostream & operator<<(std::ostream & os, const matrix & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) std::cout << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

matrix product(const matrix & lhs, const matrix & rhs) {
    if (lhs[0].size() != rhs.size()) {
        throw std::logic_error("Wrong dimensions");
    }

    int n = lhs.size(), m = rhs[0].size();
    matrix answer(n, row(m, 0));

    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t k = 0; k < rhs[0].size(); ++k) {
            for (size_t j = 0; j < lhs[0].size(); ++j) {
                answer[i][k] = (answer[i][k] + lhs[i][j] * rhs[j][k]) % 10;
            }        
        }
    }

    return answer;
}

matrix fastPow(const matrix & lhs, long long n) {
    if (n < 0) {
        throw std::logic_error("Realization don't have minus degree logic");
    }

    matrix answer(lhs.size(), row(lhs[0].size(), 0));
    for (size_t i = 0; i < lhs.size(); ++i) {
        answer[i][i] = 1;
    }

    for (int i = 62; i >= 0; --i) {
        answer = product(answer, answer);
        if (n & (1ll << i)) {
            answer = product(answer, lhs);
        }
    }

    return answer;
}

int main() {
    matrix F = {
        {0, 1},
        {1, 1}
    };

    long long n;
    std::cin >> n;
    F = fastPow(F, n + 2);
    
    // std::cout << F;
    
    std::cout << ((F[0][1] - 1) + 10) % 10 << '\n';
    return 0;
}
```
