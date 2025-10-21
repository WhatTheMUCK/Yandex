# Поиск элемента в массиве

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив `a`, состоящий из `n` чисел, и `q` запросов. Каждый запрос состоит из одного целого числа `x_i`.

Найдите и выведите индекс `p_i`, который является первым, самым левым, вхождением числа `x_i` в массив `a`. Если `x_i` не встречается среди элементов массива, то `p_i = -1`.

## Формат ввода

Первая строка содержит два разделённых пробелом числа `n` и `q` — количество чисел в массиве и количество запросов, соответственно.

Вторая строка содержит `n` чисел `a_i`, где `a_i` — число на `i`-й позиции в массиве `a`. Числа разделены пробелами.

Далее идут `q` строк, каждая строка содержит ровно одно число `x_i` — очередной запрос.

**Ограничения:**  
`1 ≤ n, q ≤ 10^5`;  
`1 ≤ a_i ≤ 10^5` для всех `1 ≤ i ≤ n`;  
`1 ≤ x_i ≤ 10^5` для всех `1 ≤ i ≤ q`.

## Формат вывода

Выведите `q` чисел `p_i`.

## Пример

Ввод:
```
5 4
4 2 1 5 2
1
2
4
6
```

Вывод:
```
3
2
1
-1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>


int lowerBound(int target, const std::vector<std::pair<int, int>> & vec) {
    int n = static_cast<int>(vec.size());
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (vec[m].first >= target) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i].first;
        vec[i].second = i;
    }
    std::sort(vec.begin(), vec.end());

    int target;
    for (int i = 0; i < q; ++i) {
        std::cin >> target;
        int targetIndex = lowerBound(target, vec);
        if (targetIndex == n || vec[targetIndex].first != target) {
            std::cout << -1 << '\n';
            continue;
        }
        std::cout << vec[targetIndex].second + 1<< '\n';
    }
    return 0;
}
```
