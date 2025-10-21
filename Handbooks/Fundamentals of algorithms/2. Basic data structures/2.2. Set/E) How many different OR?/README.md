# Сколько различных OR?

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив целых чисел длины $n$. Рассмотрим все его непустые подмассивы. Для каждого подмассива вычислим побитовый OR всех его элементов. Требуется найти число различных значений этого OR среди всех подмассивов.

## Формат входных данных

Первая строка содержит целое число $n$ ($1 \leq n \leq 2 \cdot 10^5$).  
Вторая строка содержит $n$ целых чисел $a_1, a_2, \ldots, a_n$ ($0 \leq a_i \leq 10^9$).

## Формат выходных данных

Выведите одно целое число — количество различных значений побитового OR, получающихся на подмассивах массива.

## Пример 1

**Ввод**
```
3
1 2 4
```

**Вывод**
```
6
```

## Пример 2

**Ввод**
```
4
0 0 0 0
```

**Вывод**
```
1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<int> answer;
    std::unordered_set<int> st;
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        std::unordered_set<int> cur;
        for (int value : st) {
            int curOR = value | tmp;
            cur.insert(curOR);
            answer.insert(curOR);
        }
        cur.insert(tmp);
        answer.insert(tmp);
        st = cur;
    }

    std::cout << answer.size() << '\n';

    return 0;
}
```
