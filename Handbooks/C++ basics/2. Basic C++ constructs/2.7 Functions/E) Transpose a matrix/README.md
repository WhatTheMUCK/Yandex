# Транспонировать матрицу

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Дана прямоугольная матрица `A` из `m` строк и `n` столбцов.  
**Транспонированной матрицей** $ A^T $ называется матрица из `n` строк и `m` столбцов, в которой строки и столбцы поменялись ролями: элемент $ A^T[i][j]$  равен элементу $ A[j][i] $.

Напишите функцию, которая возвращает транспонированную матрицу:

```cpp
std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>>& matrix);
```

---

## Пример

Исходная матрица:
```text
1 2 3
4 5 6
```

Транспонированная:
```text
1 4
2 5
3 6
```

---

## Примечание

- Гарантируется, что вектор `matrix` **непуст** и все его элементы имеют **равную ненулевую длину**.
- Подключите необходимые заголовочные файлы и напишите **только код функции `Transpose`**.  
  Мы скомпилируем решение с нашей функцией `main`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>> & matrix) {
    size_t row = matrix.size(), col = matrix[0].size(); // Гарантируется, что вектор matrix непуст и все его элементы имеют равную ненулевую длину.
    std::vector<std::vector<int>> answer(col, std::vector<int>(row));
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            answer[j][i] = matrix[i][j];
        }
    }
    return answer;
}

int main() {
    int row, col;
    std::cin >> row >> col;
    std::vector<std::vector<int>> matrix(row, std::vector<int>(col));
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    std::vector<std::vector<int>> matrixT = Transpose(matrix);
    for (size_t i = 0; i < col; ++i) {
        for (size_t j = 0; j < row; ++j) {
            std::cout << matrixT[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}
```
