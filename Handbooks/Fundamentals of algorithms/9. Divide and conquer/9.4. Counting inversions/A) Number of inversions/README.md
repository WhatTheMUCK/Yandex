# Количество инверсий

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дан массив $a$ из $n$ целых чисел.  
**Инверсия** — это пара индексов $(i, j)$, такая что:
- $i < j$,
- $a_i > a_j$.

Требуется найти **общее количество инверсий** в массиве.

## Формат ввода

- Первая строка: целое число $n$ — длина массива.  
- Вторая строка: $n$ целых чисел $a_0, a_1, \dots, a_{n-1}$.

**Ограничения:**  
$1 \leq n \leq 30\,000$,  
$1 \leq a_i \leq 10^9$ для всех $0 \leq i < n$.

## Формат вывода

Выведите одно целое число — количество инверсий в массиве.

## Примеры

### Пример 1

**Ввод:**
```
5
2 3 9 2 9
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
3
1 1 1
```

**Вывод:**
```
0
```

### Пример 3

**Ввод:**
```
10
1 2 1 2 1 2 3 1 3 1
```

**Вывод:**
```
12
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

long long merge(vector<long long>& arr, int left, int mid, int right) {
    vector<long long> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1); // Все элементы от i до mid образуют инверсии с arr[j]
        }
    }

    while (i <= mid)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; ++i, ++k)
        arr[i] = temp[k];

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
