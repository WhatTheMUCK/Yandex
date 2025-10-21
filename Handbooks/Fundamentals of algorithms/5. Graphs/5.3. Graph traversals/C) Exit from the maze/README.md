# Выход из лабиринта

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Задан лабиринт. Лабиринт представляет собой прямоугольник $n$ на $m$ клеток. Каждая клетка может находиться в одном из четырёх состояний:

- Пустая клетка: `.`
- Стена: `#`
- Вход в лабиринт: `S`
- Выход из лабиринта: `F`

Гарантируется, что в лабиринте ровно один вход и один выход. Также гарантируется, что контур лабиринта состоит из стены.

Изначально вы находитесь в клетке `S`. Вы можете двигаться:
- вверх — `U`,
- вниз — `D`,
- вправо — `R`,
- влево — `L`.

Требуется вывести **кратчайший путь** из лабиринта в виде строки из символов `U`, `D`, `R`, `L`.

Если выйти из лабиринта невозможно, выведите `-1`.

## Формат ввода

- В первой строке заданы два числа $n$, $m$.
- В следующих $n$ строках задан лабиринт.

## Формат вывода

- Если выйти невозможно, выведите единственное число:  
  ```
  -1
  ```
- Иначе:
  - В первой строке — длина кратчайшего пути (целое число).
  - Во второй строке — сам путь (строка из символов `U`, `D`, `R`, `L`).

## Примеры

### Пример 1

**Ввод**  
```
7 7
#######
#...#.#
#...#.#
#.#.#.#
#.#F#.#
#....S#
#######
```

**Вывод**  
```
3
LLU
```

### Пример 2

**Ввод**  
```
9 9
#########
#...#...#
#..F#.###
#...#.#.#
#.###.#.#
#.S...#.#
##..###.#
#.......#
#########
```

**Вывод**  
```
6
LUUURR
```

### Пример 3

**Ввод**  
```
11 11
###########
#.#.......#
#.#.##..###
#...#.#.#.#
#####.#.#.#
#.#.#.....#
#.#.#.#####
#.#...F.#.#
#.#S#####.#
#.........#
###########
```

**Вывод**  
```
4
URRR
```

## Ограничения

$$
1 \leq n \cdot m \leq 10^5
$$
## Решение

main.cpp
```cpp
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>


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

template <typename T, typename V>
std::pair<T, V> operator+=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator+(std::pair<T, V> lhs, const std::pair<T, V> & rhs) {
    return lhs += rhs;
}

template <typename T, typename V>
std::pair<T, V> operator-=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first -= rhs.first;
    lhs.second -= rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator-(std::pair<T, V> lhs, const std::pair<T, V> & rhs) {
    return lhs -= rhs;
}


std::vector<std::pair<int, int>> offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
std::string directions = "URDL";

std::unordered_map<char, char> reverseDirections = {{'U', 'D'}, {'R', 'L'}, {'D', 'U'}, {'L', 'R'}};

int pairToInt(const std::pair<int, int> & pos, int m) {
    auto & [i, j] = pos;
    return i * m + j;
}

std::pair<int, int> intToPair(int index, int m) {
    return {index / m, index % m};
}

bool correct(const matrix<char> & maze, int i, int j) {
    int n = static_cast<int>(maze.size());
    int m = static_cast<int>(maze[0].size());
    if (!(0 <= i && i < n) || !(0 <= j && j < m) || (maze[i][j] != '.' && maze[i][j] != 'F')) {
        return false;
    }
    return true;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<char> maze(n, row<char>(m));
    std::pair<int, int> start, finish;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> maze[i][j];
            
            if (maze[i][j] == 'S') {
                start = {i, j};
            } else if (maze[i][j] == 'F') {
                finish = {i, j};
            }
        }
    }

    matrix<char> parents = maze;

    std::queue<std::pair<int, int>> BFS;

    BFS.push({pairToInt(start, m), 0});
    while (!BFS.empty()) {
        auto [posIndex, steps] = BFS.front();
        BFS.pop(); 
        ++steps;

        std::pair<int, int> curPos = intToPair(posIndex, m);
        for (int k = 0; k < 4; ++k) {
            std::pair<int, int> tempPos = curPos + offsets[k];
            auto & [i, j] = tempPos;
            if (correct(parents, i, j)) {
                parents[i][j] = directions[k];

                if (maze[i][j] == 'F') {
                    std::cout << steps << '\n';
                    std::string path;
                    while (parents[i][j] != 'S') {
                        path.push_back(parents[i][j]);
                        char direction = reverseDirections[parents[i][j]];
                        int offsetIndex = directions.find(direction);
                        tempPos += offsets[offsetIndex];
                    }
                    std::reverse(path.begin(), path.end());
                    std::cout << path << '\n';
                    return 0;
                }

                BFS.push({pairToInt(tempPos, m), steps});
            }
        }
    }

    std::cout << "-1\n";
    return 0;
}
```
