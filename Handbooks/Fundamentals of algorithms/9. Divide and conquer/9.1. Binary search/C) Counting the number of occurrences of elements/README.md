# Подсчёт количества вхождений элементов

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дан **отсортированный по неубыванию** массив $K$ из $n$ целых чисел (возможны повторения).  
Также задан массив запросов $Q = [q_0, q_1, \dots, q_{m-1}]$.

Для каждого запроса $q_i$ требуется определить **количество вхождений** значения $q_i$ в массиве $K$.

## Формат ввода

- Первая строка: целое число $n$ — размер массива $K$.  
- Вторая строка: $n$ целых чисел $k_0 \leq k_1 \leq \dots \leq k_{n-1}$.  
- Третья строка: целое число $m$ — количество запросов.  
- Четвёртая строка: $m$ целых чисел $q_0, q_1, \dots, q_{m-1}$.

**Ограничения:**  
$1 \leq n \leq 10^5$,  
$1 \leq m \leq 10^5$,  
$1 \leq k_i \leq 10^9$ для всех $0 \leq i < n$,  
$1 \leq q_j \leq 10^9$ для всех $0 \leq j < m$.

## Формат вывода

Выведите $m$ целых чисел через пробел — для каждого $i$ от $0$ до $m-1$ количество индексов $j$, таких что $k_j = q_i$.

## Пример

**Ввод:**
```
7
1 2 2 2 4 4 9
5
1 2 3 4 5
```

**Вывод:**
```
1 3 0 2 0
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

int binarySearch(const std::vector<int> & data, int query) {
    int n = static_cast<int>(data.size());
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (data[m] >= query) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> k(n);
    std::cin >> k;

    std::cin >> m;
    std::vector<int> q(m);
    std::cin >> q;

    for (int i = 0; i < m; ++i) {
        if (i > 0) std::cout << ' ';
        int l = binarySearch(k, q[i]);
        int r = binarySearch(k, q[i] + 1);
        if (l == n || k[l] != q[i]) {
            std::cout << "0";
            continue;
        } 

        std::cout << (r - l);
    }
    std::cout << '\n';    

    return 0;
}
```
