# ArgMax в матрице

**Ограничение времени**  
1 с

**Ограничение памяти**  
64.0 Мб

**Ввод**  
стандартный ввод или `input.txt`

**Вывод**  
стандартный вывод или `output.txt`

---

Вам требуется написать на C++ функцию со следующим заголовком:

```
std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>>& matrix);
```

Функция должна вернуть пару из индексов максимального элемента в матрице.  
Если максимальных элементов несколько, то нужно вернуть **наименьшую такую пару** (сначала сравниваем по строке, потом по столбцу — как в лексикографическом порядке).

---

## Формат ввода

В первой строке двумя числами `n` и `k` задан размер матрицы.  
В последующих `n` строках вводится числовая матрица в `k` столбцов.

---

## Формат вывода

Индекс строки и столбца максимального элемента в матрице.

---

## Пример 1

**Ввод:**
```
3 4
0 3 2 4
2 3 5 5
5 1 2 3
```

**Вывод:**
```
1 2
```

---

## Пример 2

**Ввод:**
```
1 1
1
```

**Вывод:**
```
0 0
```

---

## Пример 3

**Ввод:**
```
3 5
1 2 3 4 5
6 7 8 9 10
11 12 13 14 15
```

**Вывод:**
```
2 4
```

---

## Примечание

Считайте, что матрица задана корректно: все строки одинаковой длины, пустых строк нет. В матрице всегда есть хотя бы один элемент.

Подключите необходимые заголовочные файлы и напишите **только код функции `MatrixArgMax`**.  
Мы скомпилируем решение с нашей функцией `main`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <utility>
#include <vector>

std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>> & matrix) {
    std::pair<size_t, size_t> answer = {0, 0};
    int maxNumber = matrix[0][0];
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            if (maxNumber < matrix[i][j]) {
                answer = {i, j};
                maxNumber = matrix[i][j];
            }
        }
    }
    return answer;
}

std::ostream & operator<<(std::ostream & os, const std::pair<size_t, size_t> pair) {
    return os << pair.first << ' ' << pair.second;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(k));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    std::cout << MatrixArgMax(matrix) << '\n';
    return 0;
}
```
