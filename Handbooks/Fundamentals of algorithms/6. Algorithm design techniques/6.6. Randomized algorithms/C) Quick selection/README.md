# Быстрый выбор

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив из $n$ целых чисел. Требуется найти **$k$-й по величине элемент** в порядке **неубывания**  
(т.е. 1-й — минимальный, $n$-й — максимальный).

Если в массиве есть равные элементы, счёт ведётся по позициям в **отсортированном по неубыванию массиве**.

## Формат входных данных

- Первая строка содержит два целых числа $n$ и $k$  
  ($1 \leq n \leq 2 \cdot 10^5$, $1 \leq k \leq n$).
- Вторая строка содержит $n$ целых чисел $a_1, a_2, \dots, a_n$  
  ($-10^9 \leq a_i \leq 10^9$).

## Формат выходных данных

Выведите одно целое число — значение **$k$-го** по величине элемента массива в порядке неубывания.

## Примечания

- Порядок индексации по $k$ — **с единицы**.
- Например, для массива `5 1 1 7` при $k = 2$ ответ равен `1`.
- Эффективное решение: алгоритм **быстрого выбора** (`QuickSelect`) с ожидаемой сложностью $O(n)$ и $O(1)$ дополнительной памяти.

## Примеры

### Пример 1

**Ввод:**
```
5 2
3 1 4 1 5
```

**Вывод:**
```
1
```

### Пример 2

**Ввод:**
```
6 5
-2 7 7 0 -2 10
```

**Вывод:**
```
7
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int quickSelect(std::vector<long long>& arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = std::uniform_int_distribution<int>(left, right)(rng);
    std::swap(arr[pivotIndex], arr[right]);

    long long pivot = arr[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    int j = i;
    for (int k = i; k < right; ++k) {
        if (arr[k] == pivot) {
            std::swap(arr[j], arr[k]);
            ++j;
        }
    }
    std::swap(arr[j], arr[right]);

    // Теперь:
    // [left, i)       — < pivot
    // [i, j]          — == pivot
    // (j, right]      — > pivot

    int leftCount = i - left;
    int equalCount = j - i + 1;

    if (k <= leftCount) {
        return quickSelect(arr, left, i - 1, k);
    } else if (k <= leftCount + equalCount) {
        return pivot;
    } else {
        return quickSelect(arr, j + 1, right, k - leftCount - equalCount);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long result = quickSelect(a, 0, n - 1, k);
    std::cout << result << '\n';

    return 0;
}
```
