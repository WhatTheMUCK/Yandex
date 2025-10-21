# Быстрая сортировка

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Реализуйте алгоритм **быстрой сортировки** (`QuickSort`).

Алгоритм:
1. Выбрать **опорный элемент** (pivot) из массива.
2. Разделить массив на две части:
   - элементы **меньше или равные** опорному,
   - элементы **больше** опорного.
3. Рекурсивно применить быструю сортировку к обеим частям.
4. Объединить результат.

> Для этой задачи допускается любой корректный выбор опорного элемента (например, первый, последний, случайный или средний), главное — корректная и эффективная реализация.

## Формат ввода

- В первой строке задано число $n$ ($1 \leq n \leq 100\,000$).
- Во второй строке задано $n$ целых чисел $a_i$ ($1 \leq a_i \leq 10^9$).

## Формат вывода

Выведите массив, отсортированный по неубыванию, через пробел.

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
1 11 1
```

**Вывод:**
```
1 1 11
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <chrono>


static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

size_t lomutoPartition(std::vector<int>& vec, size_t l, size_t r) {
    std::uniform_int_distribution<size_t> dist(l, r);
    size_t randomIndex = dist(rng);
    std::swap(vec[randomIndex], vec[r]);

    int pivot = vec[r];
    size_t i = l;
    for (size_t j = l; j < r; ++j) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[r]);
    return i;
}

void quickSort(std::vector<int>& vec, size_t l, size_t r) {
    if (l >= r) return;

    size_t p = lomutoPartition(vec, l, r);
    if (p > 0) {
        quickSort(vec, l, p - 1);
    }
    quickSort(vec, p + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    quickSort(vec, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';

    return 0;
}
```
