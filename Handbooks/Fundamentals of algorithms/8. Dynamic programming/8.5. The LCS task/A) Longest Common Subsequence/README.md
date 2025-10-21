# Наибольшая общая подпоследовательность

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Даны две последовательности:  
$A = (a_1, a_2, \dots, a_n)$ и $B = (b_1, b_2, \dots, b_m)$.

Их **общая подпоследовательность** длиной $p$ — это пара строго возрастающих наборов индексов  
$$
1 \leq i_1 < i_2 < \dots < i_p \leq n,\quad
1 \leq j_1 < j_2 < \dots < j_p \leq m,
$$  
таких что  
$$
a_{i_1} = b_{j_1},\;
a_{i_2} = b_{j_2},\;
\dots,\;
a_{i_p} = b_{j_p}.
$$

**Наибольшая общая подпоследовательность (НОП)** — это общая подпоследовательность **максимальной длины**.

Эта задача применяется в:
- сопоставлении данных (например, утилита `diff`),
- системах управления версиями (операция слияния),
- биоинформатике (сравнение геномов) и других областях.

## Формат ввода

- Первая строка: целое число $n$ — длина первой последовательности.  
- Вторая строка: $n$ целых чисел $a_1, a_2, \dots, a_n$.  
- Третья строка: целое число $m$ — длина второй последовательности.  
- Четвёртая строка: $m$ целых чисел $b_1, b_2, \dots, b_m$.

**Ограничения:**  
$1 \leq n, m \leq 100$,  
$-10^9 \leq a_i, b_i \leq 10^9$ для всех $i$.

## Формат вывода

Выведите одно целое число — **длину наибольшей общей подпоследовательности**.

## Примеры

### Пример 1

**Ввод:**
```
5
1 2 5 4 9
8
18 3 2 8 0 4 7 9
```

**Вывод:**
```
3
```

### Пример 2

**Ввод:**
```
2
1 1
3
1 1 1
```

**Вывод:**
```
2
```

### Пример 3

**Ввод:**
```
3
13 17 37
5
37 73 13 31 23
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

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> firstSubsequence(n);
    std::cin >> firstSubsequence;

    std::cin >> m;
    std::vector<int> secondSubsequence(m);
    std::cin >> secondSubsequence;
    std::vector<std::vector<int>> LCS(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int deletionFirst = LCS[i - 1][j];
            int deletionSecond = LCS[i][j - 1];
            int match = LCS[i - 1][j - 1] + 1;
            LCS[i][j] = std::max(deletionFirst, deletionSecond);
            if (firstSubsequence[i - 1] == secondSubsequence[j - 1]) {
                LCS[i][j] = std::max(LCS[i][j], match);
            }
        }
    }

    std::cout << LCS[n][m] << '\n';
    return 0; 
}
```
