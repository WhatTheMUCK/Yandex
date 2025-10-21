# Сортировка слиянием

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Реализуйте **сортировку слиянием** — эффективный алгоритм сортировки, основанный на принципе «разделяй и властвуй».

Алгоритм:
1. Разделить массив на две примерно равные половины.
2. Рекурсивно отсортировать каждую половину.
3. Слить две отсортированные половины в один отсортированный массив.

## Формат ввода

- В первой строке задано число $n$ ($1 \leq n \leq 100\,000$).
- Во второй строке задано $n$ целых чисел $a_i$ ($0 \leq a_i \leq 10^9$).

## Формат вывода

Выведите отсортированный по неубыванию массив чисел через пробел.

## Примеры

### Пример 1

**Ввод:**
```
7
13 17 37 73 31 19 23
```

**Вывод:**
```
13 17 19 23 31 37 73
```

### Пример 2

**Ввод:**
```
4
18 20 3 17
```

**Вывод:**
```
3 17 18 20
```

### Пример 3

**Ввод:**
```
3
0 11 0
```

**Вывод:**
```
0 0 11
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

std::ostream & operator<<(std::ostream & os, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (i > 0) os << ' ';
        os << rhs[i];
    }
    os << '\n';
    return os;
}

void merge(int start1, int end1, int start2, int end2, std::vector<int> & vec) {
    std::vector<int> answer;
    int lhsIndex = start1, rhsIndex = start2;
    while (lhsIndex <= end1 && rhsIndex <= end2) {
        if (vec[lhsIndex] <= vec[rhsIndex]) {
            answer.push_back(vec[lhsIndex]);
            ++lhsIndex;
        } else {
            answer.push_back(vec[rhsIndex]);
            ++rhsIndex;
        }
    }

    for (; lhsIndex <= end1; ++lhsIndex) {
        answer.push_back(vec[lhsIndex]);
    }

    for (; rhsIndex <= end2; ++rhsIndex) {
        answer.push_back(vec[rhsIndex]);
    }

    for (int i = 0; i <= end2 - start1; ++i) {
        vec[start1 + i] = answer[i];
    }
    return;
}

void mergeSort(std::vector<int> & vec, int l, int r) {
    if (l == r) {
        return;
    }

    int middle = (l + r) / 2;
    mergeSort(vec, l, middle);
    mergeSort(vec, middle + 1, r);
    merge(l, middle, middle + 1, r, vec);
    return;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> answer(n);
    std::cin >> answer;

    mergeSort(answer, 0, n - 1);

    std::cout << answer;
    return 0;
}
```
