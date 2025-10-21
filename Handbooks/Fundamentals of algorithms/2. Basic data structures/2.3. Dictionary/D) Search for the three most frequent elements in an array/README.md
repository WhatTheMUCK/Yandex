# Поиск трёх самых частых элементов в массиве

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив $a$, состоящий из $n$ чисел.

Найдите три **различных** элемента этого массива $x_1$, $x_2$, $x_3$, которые **суммарно** встречаются наибольшее количество раз.

Если подходящих троек элементов $x_1$, $x_2$, $x_3$ несколько, то выведите тройку с **наименьшей суммой значений**.

Гарантируется, что массив содержит **не менее 3 различных элементов**.

## Формат ввода

Первая строка содержит единственное число $n$ — количество чисел в массиве.

Вторая строка содержит $n$ чисел $a_i$, где $a_i$ — число на $i$-й позиции в массиве $a$.  
Числа разделены пробелами.

**Ограничения:**  
$1 \leq n \leq 10^5$;  
$1 \leq a_i \leq 10^5$ для всех $1 \leq i \leq n$.

## Формат вывода

Выведите три числа $x_1$, $x_2$, $x_3$, **разделённых пробелами**, в порядке **возрастания**.

## Пример 1

**Ввод**
```
6
1 2 3 2 1 1
```

**Вывод**
```
1 2 3
```

## Пример 2

**Ввод**
```
6
3 1 1 2 3 3
```

**Вывод**
```
1 2 3
```

## Пример 3

**Ввод**
```
8
11 21 31 41 31 41 11 21
```

**Вывод**
```
11 21 31
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        ++mp[a];
    }

    std::vector<std::pair<int, int>> vec;
    for (const std::pair<const int, int> & pair : mp) {
        vec.push_back(pair);
    }

    std::sort(vec.begin(), vec.end(), [](const std::pair<int, int> & lhs, const std::pair<int, int> & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first); 
    });

    std::vector<int> answer;
    for (int i = 0; i < 3; ++i) {
        answer.push_back(vec[i].first); 
    }

    std::sort(answer.begin(), answer.end());

    for (int i = 0; i < 3; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}
```
