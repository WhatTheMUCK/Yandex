# Подсчёт транспозиций (усложнённая)

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Дана перестановка $p$ из $n$ целых чисел.

Будем говорить, что перестановка **упорядочена хорошо**, если существует такое целое число $x$ ($1 \leq x \leq n$), что перестановка имеет вид:

$$
x,\, x+1,\, x+2,\, \dots,\, n,\, 1,\, 2,\, \dots,\, x-1.
$$

То есть это **циклический сдвиг** возрастающей последовательности $[1, 2, \dots, n]$.

**Транспозиция** — это обмен **двух соседних** элементов местами.

Требуется найти **минимальное количество транспозиций**, необходимых для приведения исходной перестановки к **любому** из таких «хорошо упорядоченных» видов.

## Формат ввода

- Первая строка: целое число $n$ — длина перестановки.  
- Вторая строка: $n$ различных целых чисел $p_0, p_1, \dots, p_{n-1}$, образующих перестановку чисел от $1$ до $n$.

**Ограничения:**  
$1 \leq n \leq 30\,000$,  
$1 \leq p_i \leq n$, все $p_i$ попарно различны.

## Формат вывода

Выведите одно целое число — **минимальное количество соседних обменов (транспозиций)**, необходимых для преобразования перестановки в один из «хорошо упорядоченных» видов.

## Пример

**Ввод:**
```
5
3 5 4 2 1
```

**Вывод:**
```
2
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long merge_count(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
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

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; ++i, ++k)
        arr[i] = temp[k];

    return inv_count;
}

long long merge_sort_count(vector<int>& arr, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_count(arr, left, mid);
        inv_count += merge_sort_count(arr, mid + 1, right);
        inv_count += merge_count(arr, left, mid, right);
    }
    return inv_count;
}

long long count_inversions(vector<int> a) {
    return merge_sort_count(a, 0, (int)a.size() - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    vector<int> pos(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    // Инверсии для x = 1
    long long current = count_inversions(p);
    long long best = current;

    // Перебираем x = 2 ... n
    for (int x = 2; x <= n; ++x) {
        int i = pos[x - 1]; // позиция элемента, который уходит в конец
        current += (n - 1 - 2LL * i);
        if (current < best) best = current;
    }

    cout << best << '\n';

    return 0;
}
```
