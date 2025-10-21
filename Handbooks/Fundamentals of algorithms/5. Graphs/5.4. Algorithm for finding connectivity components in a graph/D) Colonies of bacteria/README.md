# Колонии бактерий

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В чашке Петри выращивают бактерии. Поверхность чашки представлена в виде прямоугольной решётки размером $n \times m$. Некоторые клетки содержат бактерии, остальные пусты.

Будем считать, что клетки с бактериями принадлежат одной колонии, если они соприкасаются по стороне. Таким образом, колония — это связная область из занятых клеток.

Нужно найти количество колоний и размер наибольшей из них.

## Формат входных данных

- В первой строке заданы два числа $n$ и $m$ ($1 \leq n, m \leq 1000$) — размеры решётки.
- В следующих $n$ строках содержится по $m$ символов:
  - `#` — клетка с бактерией,
  - `.` — пустая клетка.

## Формат выходных данных

- В первой строке выведите число $k$ — количество колоний.
- Во второй строке выведите число — размер наибольшей колонии.

## Примеры

### Пример 1

**Ввод**  
```
5 6
..##..
..##..
.#....
###..#
.#..#.
```

**Вывод**  
```
4
5
```

### Пример 2

**Ввод**  
```
4 5
#...#
.#..#
..##.
#....
```

**Вывод**  
```
5
2
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <queue>


template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::istream & operator>>(std::istream & is, matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            is >> rhs[i][j];
        }
    }
    return is;
}

template <typename T>
std::ostream & operator<<(std::ostream & os, matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

template <typename T, typename V>
std::pair<T, V> & operator+=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator+(std::pair<T, V> lhs, const std::pair<T, V> & rhs) {
    return lhs += rhs;
}

std::vector<std::pair<int, int>> offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

template <typename T>
bool correct(const matrix<T> & cup, int i, int j, matrix<bool> & visited) {
    int n = static_cast<int>(cup.size());
    int m = static_cast<int>(cup[0].size());
    if (!(0 <= i && i < n) || !(0 <= j && j < m)) {
        return false;
    }

    if (cup[i][j] == '.') {
        visited[i][j] = true;
    }

    if (visited[i][j]) {
        return false;
    }

    return true;
}

template <typename T>
int bfs(const matrix<T> & cup, int i, int j, matrix<bool> & visited) {
    std::queue<std::pair<int, int>> BFS;
    BFS.push({i, j});
    visited[i][j] = true;
    int amountOfBacterias = 1;
    while (!BFS.empty()) {
        std::pair<int, int> curPos = BFS.front();
        BFS.pop();

        for (std::pair<int, int> offset : offsets) {
            auto [tempI, tempJ] = curPos + offset;
            if (correct(cup, tempI, tempJ, visited)) {
                ++amountOfBacterias;
                visited[tempI][tempJ] = true;
                BFS.push({tempI, tempJ});
            }
        }
    }

    return amountOfBacterias;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<char> cup(n, row<char>(m, '.'));
    std::cin >> cup;

    matrix<bool> visited(n, row<bool>(m, false));
    int maxAmountOfBacterias = 0;
    int colonies = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {  
            if (visited[i][j]) {
                continue;
            }

            if (cup[i][j] == '.') {
                visited[i][j] = true;
                continue;
            }

            maxAmountOfBacterias = std::max(bfs(cup, i, j, visited), maxAmountOfBacterias);
            ++colonies;
        }
    }

    std::cout << colonies << '\n' << maxAmountOfBacterias << '\n';
    return 0;
}
```
