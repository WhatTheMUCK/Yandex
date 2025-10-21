# Количество полуинверсий

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дан массив $a$ из $n$ целых чисел.  
**Полуинверсия** — это пара индексов $(i, j)$, такая что:
- $i < j$,
- $a_i \geq a_j$.

Требуется найти **общее количество полуинверсий** в массиве.

> Обратите внимание: в отличие от обычных инверсий (где требуется строгое неравенство $a_i > a_j$), здесь допускается равенство.

## Формат ввода

- Первая строка: целое число $n$ — длина массива.  
- Вторая строка: $n$ целых чисел $a_0, a_1, \dots, a_{n-1}$.

**Ограничения:**  
$1 \leq n \leq 30\,000$,  
$1 \leq a_i \leq 10^9$ для всех $0 \leq i < n$.

## Формат вывода

Выведите одно целое число — количество полуинверсий в массиве.

## Примеры

### Пример 1

**Ввод:**
```
5
2 3 9 2 9
```

**Вывод:**
```
4
```

### Пример 2

**Ввод:**
```
3
1 1 1
```

**Вывод:**
```
3
```

### Пример 3

**Ввод:**
```
10
1 2 1 2 1 2 3 1 3 1
```

**Вывод:**
```
26
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

long long merge(vector<long long>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<long long> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    long long inv_count = 0;

    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            arr[k++] = L[i++];
        } else {
            // L[i] >= R[j] - полуинверсия
            arr[k++] = R[j++];
            inv_count += (n1 - i); // все элементы от i до n1-1 в L >= R[j]
        }
    }

    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    return inv_count;
}

long long mergeSort(vector<long long>& arr, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += mergeSort(arr, left, mid);
        inv_count += mergeSort(arr, mid + 1, right);
        inv_count += merge(arr, left, mid, right);
    }
    return inv_count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    long long result = mergeSort(a, 0, n - 1);
    cout << result << '\n';

    return 0;
}
```
