# Модификация быстрой сортировки

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дана последовательность $a$ из $n$ целых чисел (возможны повторяющиеся элементы).

Исходный алгоритм `RandomizedQuickSort` разбивает массив на две части:
- элементы **меньше** опорного,
- элементы **больше** опорного,

и рекурсивно сортирует их. Однако при большом количестве **повторяющихся элементов** такая реализация может деградировать до $O(n^2)$, так как все повторяющиеся значения оказываются в одной из частей.

Чтобы гарантировать **ожидаемое время работы** $O(n \log n)$ даже при наличии множества одинаковых элементов, необходимо модифицировать разбиение:  
разделять массив на **три части**:
- элементы **меньше** опорного,
- элементы **равные** опорному,
- элементы **больше** опорного.

Такой подход называется **трёхсторонним разбиением** (или **Dutch National Flag partitioning**).

## Формат ввода

- Первая строка: целое число $n$ — длина последовательности.  
- Вторая строка: $n$ целых чисел $a_0, a_1, \dots, a_{n-1}$.

**Ограничения:**  
$1 \leq n \leq 10^5$,  
$1 \leq a_i \leq 10^9$ для всех $0 \leq i < n$.

## Формат вывода

Выведите последовательность в **неубывающем порядке**, разделённую пробелами.

## Примеры

### Пример 1

**Ввод:**
```
5
2 3 9 2 2
```

**Вывод:**
```
2 2 2 3 9
```

### Пример 2

**Ввод:**
```
4
1 2 3 1
```

**Вывод:**
```
1 1 2 3
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::mt19937 rng(std::random_device{}());

std::vector<int> randomizedQuickSort(const std::vector<int>& a) {
    if (a.size() <= 1) {
        return a;
    }

    // Выбираем случайный опорный элемент
    int pivot = a[std::uniform_int_distribution<int>(0, a.size() - 1)(rng)];

    std::vector<int> less, equal, greater;
    for (int x : a) {
        if (x < pivot) {
            less.push_back(x);
        } else if (x == pivot) {
            equal.push_back(x);
        } else {
            greater.push_back(x);
        }
    }

    // Рекурсивно сортируем меньшие и большие
    auto sorted_less = randomizedQuickSort(less);
    auto sorted_greater = randomizedQuickSort(greater);

    // Собираем результат
    sorted_less.insert(sorted_less.end(), equal.begin(), equal.end());
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());

    return sorted_less;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto result = randomizedQuickSort(a);

    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << result[i];
    }
    std::cout << '\n';

    return 0;
}
```
