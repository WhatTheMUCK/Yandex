# Дружный граф

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Даны несколько «дружных» групп людей. Внутри каждой группы каждый дружит с каждым. Некоторые люди могут входить в несколько групп, группы могут пересекаться.

Требуется построить общий граф дружбы из $n$ вершин и вывести его в виде матрицы смежности.

## Формат входных данных

Первая строка содержит целое число $g$ — количество групп ($1 \leq g \leq 10^5$).

Далее идут $g$ строк. Каждая строка описывает одну группу:  
```
k v₁ v₂ … vₖ
```  
где  
- $k$ — размер группы ($1 \leq k \leq n \leq 100$),  
- $v_i$ — идентификаторы людей ($1 \leq v_i \leq n$).

Идентификаторы не обязаны идти подряд и могут повторяться в разных группах.  
Гарантируется, что внутри одной группы все $v_i$ попарно различны.

## Формат выходных данных

В первой строке выведите $n$.  
Далее выведите $n$ строк по $n$ чисел — матрицу смежности $A$ построенного графа:  
$A[i][j] = 1$, если люди с номерами $i+1$ и $j+1$ дружат, и $0$ иначе.

## Примеры

### Пример 1

**Ввод**  
```
3
3 1 2 3
2 2 4
1 5
```

**Вывод**  
```
5
0 1 1 0 0
1 0 1 1 0
1 1 0 0 0
0 1 0 0 0
0 0 0 0 0
```

### Пример 2

**Ввод**  
```
2
3 1 2 3
2 2 4
```

**Вывод**  
```
4
0 1 1 0
1 0 1 1
1 1 0 0
0 1 0 0
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int g, n = 1;
    matrix<int> graph(100, row<int>(100, 0));
    std::cin >> g;
    for (int i = 0; i < g; ++i) {
        int k;
        std::cin >> k;
        std::vector<int> friends(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> friends[j];
            n = std::max(n, friends[j]);
        }

        for (int j1 = 0; j1 < k; ++j1) {
            for (int j2 = j1 + 1; j2 < k; ++j2) {
                int prev = friends[j1] - 1, cur = friends[j2] - 1;
                graph[cur][prev] = 1;
                graph[prev][cur] = 1;
            }
        }
    }

    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) std::cout << ' ';
            std::cout << graph[i][j];
        }
        std::cout << '\n';
    }
    
    return 0;
}


```
