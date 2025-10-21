# Матрица достижимости

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Задан ориентированный граф из $n$ вершин. Граф задан матрицей смежности. Требуется построить матрицу достижимости этого графа.

Матрица достижимости $R$ определяется так:  
$R[i][j] = 1$, если существует путь из вершины $i$ в вершину $j$, и $R[i][j] = 0$ иначе.

## Формат входных данных

- В первой строке задано число $n$ — количество вершин графа ($1 \leq n \leq 100$).
- Далее следует $n$ строк по $n$ чисел — матрица смежности графа.  
  Элемент $a_{ij}$ равен $1$, если из вершины $i$ существует ребро в вершину $j$, и $0$ иначе.

## Формат выходных данных

Выведите $n$ строк по $n$ чисел — матрицу достижимости графа.

## Примеры

### Пример 1

**Ввод**  
```
4
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
```

**Вывод**  
```
1 1 1 1
1 1 1 1
1 1 1 1
1 1 1 1
```

### Пример 2

**Ввод**  
```
6
1 1 1 0 0 0
1 1 1 0 0 0
1 1 1 0 0 0
0 0 0 1 1 1
0 0 0 1 1 1
0 0 0 1 1 1
```

**Вывод**  
```
1 1 1 0 0 0
1 1 1 0 0 0
1 1 1 0 0 0
0 0 0 1 1 1
0 0 0 1 1 1
0 0 0 1 1 1
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


template <typename T>
matrix<T> customProduct(const matrix<T> & lhs, const matrix<T> & rhs, matrix<T> & main){
    matrix<T> answer(lhs.size(), row<T>(lhs[0].size(), 0));
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            for (size_t k = 0; k < lhs[0].size(); ++k) {
                answer[i][j] += lhs[i][k] * rhs[k][j];
            }
            answer[i][j] = std::min(answer[i][j], 1);
            main[i][j] = std::max(main[i][j], answer[i][j]);
        }
    }
    return answer;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    matrix<int> startGraph(n, row<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> startGraph[i][j];
        }
    }
    matrix<int> helper = startGraph, answer = startGraph;
    for (int i = 1; i < n; ++i) {
        helper = customProduct(helper, startGraph, answer);
    }

    std::cout << answer;

    return 0;   
}


```
