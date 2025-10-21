# Наибольшая общая подпоследовательность трех последовательностей

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Даны три последовательности:  
- $A = (a_1, a_2, \dots, a_n)$,  
- $B = (b_1, b_2, \dots, b_m)$,  
- $C = (c_1, c_2, \dots, c_l)$.

Требуется найти **длину наибольшей общей подпоследовательности (НОП)** для всех трёх последовательностей одновременно.

Формально, нужно найти наибольшее целое число $p \geq 0$, для которого существуют строго возрастающие наборы индексов:
- $1 \leq i_1 < i_2 < \dots < i_p \leq n$,
- $1 \leq j_1 < j_2 < \dots < j_p \leq m$,
- $1 \leq k_1 < k_2 < \dots < k_p \leq l$,

такие что для всех $t = 1, 2, \dots, p$ выполняется:
$$
a_{i_t} = b_{j_t} = c_{k_t}.
$$

## Формат ввода

- Первая строка: $n$ — длина первой последовательности.  
- Вторая строка: $n$ целых чисел $a_1, a_2, \dots, a_n$.  
- Третья строка: $m$ — длина второй последовательности.  
- Четвёртая строка: $m$ целых чисел $b_1, b_2, \dots, b_m$.  
- Пятая строка: $l$ — длина третьей последовательности.  
- Шестая строка: $l$ целых чисел $c_1, c_2, \dots, c_l$.

**Ограничения:**  
$1 \leq n, m, l \leq 100$,  
$-10^9 \leq a_i, b_i, c_i \leq 10^9$.

## Формат вывода

Выведите одно целое число — **длину наибольшей общей подпоследовательности** трёх заданных последовательностей.

## Примеры

### Пример 1

**Ввод:**
```
4
1 2 3 4
4
3 2 4 1
3
3 2 4
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
3
1 2 4
2
2 4
4
4 2 2 1
```

**Вывод:**
```
1
```

### Пример 3

**Ввод:**
```
3
5 19 18
2
19 7
4
1 19 2 45
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
    int n, m, l;
    std::cin >> n;
    std::vector<int> firstSubsequence(n);
    std::cin >> firstSubsequence;

    std::cin >> m;
    std::vector<int> secondSubsequence(m);
    std::cin >> secondSubsequence;

    std::cin >> l;
    std::vector<int> thirdSubsequence(l);
    std::cin >> thirdSubsequence;

    std::vector<std::vector<std::vector<int>>> LCS(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(l + 1, 0)));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= l; ++k) {
                int deletionFirst = LCS[i - 1][j][k];
                int deletionSecond = LCS[i][j - 1][k];
                int deletionThird = LCS[i][j][k - 1];
                int match = LCS[i - 1][j - 1][k - 1] + 1;
                LCS[i][j][k] = std::max({deletionFirst, deletionSecond, deletionThird});
                if (firstSubsequence[i - 1] == secondSubsequence[j - 1] && secondSubsequence[j - 1] == thirdSubsequence[k - 1]) {
                    LCS[i][j][k] = std::max(LCS[i][j][k], match);
                }
            }
        }
    }

    std::cout << LCS[n][m][l] << '\n';
    return 0; 
}
```
