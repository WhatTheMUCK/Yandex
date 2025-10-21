# Подсчёт транспозиций

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дана перестановка $p$ из $n$ целых чисел.  
**Транспозиция** — это обмен **двух соседних** элементов местами.

Требуется найти **минимальное количество транспозиций**, необходимых для сортировки перестановки по возрастанию.

> Известно, что минимальное число таких обменов равно **количеству инверсий** в перестановке.

## Формат ввода

- Первая строка: целое число $n$ — длина перестановки.  
- Вторая строка: $n$ различных целых чисел $p_0, p_1, \dots, p_{n-1}$, образующих перестановку чисел от $1$ до $n$.

**Ограничения:**  
$1 \leq n \leq 30\,000$,  
$1 \leq p_i \leq n$, все $p_i$ попарно различны.

## Формат вывода

Выведите одно целое число — **минимальное количество транспозиций**, необходимых для сортировки перестановки.

## Пример

**Ввод:**
```
5
3 5 4 2 1
```

**Вывод:**
```
8
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
            inv_count += (mid - i + 1);
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
