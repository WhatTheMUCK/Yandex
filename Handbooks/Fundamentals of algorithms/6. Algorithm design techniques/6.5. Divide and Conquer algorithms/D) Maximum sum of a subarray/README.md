# Максимальная сумма подмассива

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив из $n$ целых чисел $a_1, a_2, \dots, a_n$.  
Найдите **максимальную возможную сумму непустого непрерывного подмассива**.

Формально, требуется вычислить:

$$
\max_{1 \leq L \leq R \leq n} \sum_{i=L}^{R} a_i
$$

## Формат ввода

- Первая строка содержит целое число $n$ ($1 \leq n \leq 2 \cdot 10^5$).
- Вторая строка содержит $n$ целых чисел $a_i$ ($|a_i| \leq 10^9$).

## Формат вывода

Выведите одно целое число — максимальную сумму непрерывного подмассива.

## Примеры

### Пример 1

**Ввод:**
```
5
-2 1 -3 4 -1
```

**Вывод:**
```
4
```

### Пример 2

**Ввод:**
```
8
-2 1 -3 4 -1 2 1 -5
```

**Вывод:**
```
6
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>


std::istream & operator>>(std::istream & is, std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        is >> vec[i];
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) os << ' ';
        os << vec[i];
    }
    return os;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    std::cin >> vec;
    long long maxSum = std::numeric_limits<int>::min(), minSum = 0, curSum = 0;
    for (int value : vec) {
        curSum += value;
        maxSum = std::max({maxSum, curSum, curSum - minSum});
        minSum = std::min(minSum, curSum);
    }

    std::cout << maxSum << '\n';
    return 0;
}
```
