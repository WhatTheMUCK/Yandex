# Выход из лабиринта: один ключ

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Задан лабиринт. Лабиринт представляет собой прямоугольник $n$ на $m$ клеток. Каждая клетка может находиться в одном из шести состояний:

- Пустая клетка: `.`
- Стена: `#`
- Вход в лабиринт: `S`
- Выход из лабиринта: `F`
- Дверь с замком: `D`
- Ключ от двери: `K`

Гарантируется, что в лабиринте ровно один вход, один выход, одна дверь и один ключ. Также гарантируется, что контур лабиринта состоит из стены.

Изначально вы находитесь в клетке `S`. Вы можете выполнять следующие действия:

- Двигаться вверх — `U`
- Двигаться вниз — `D`
- Двигаться вправо — `R`
- Двигаться влево — `L`
- Подобрать ключ — `P` (только если вы находитесь в клетке с ключом `K`)

Ключ можно подобрать только один раз. После подбора ключа вы можете проходить через клетку `D`. До этого клетка `D` недоступна (считается как стена).

Требуется вывести **кратчайший путь** из лабиринта в виде строки из символов `U`, `D`, `R`, `L`, `P`.

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
  - Во второй строке — сам путь (строка из символов `U`, `D`, `R`, `L`, `P`).

## Примеры

### Пример 1

**Ввод**  
```
7 7
#######
#K..#F#
#...#D#
#.#.#.#
#.#.#.#
#....S#
#######
```

**Вывод**  
```
21
LLLLUUUUPDDDDRRRRUUUU
```

### Пример 2

**Ввод**  
```
7 7
#######
#...#.#
#.D.#.#
#.#.#K#
#.#F#.#
#....S#
#######
```

**Вывод**  
```
3
LLU
```

### Пример 3

**Ввод**  
```
7 7
#######
#F#..K#
#.#...#
#.#.#.#
#.###S#
#D....#
#######
```

**Вывод**  
```
16
UUUPDDDDLLLLUUUU
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

long long pairToInt(const std::pair<int, int> & pos, int m) {
    auto & [i, j] = pos;
    return i * m + j;
}

std::pair<int, int> intToPair(long long index, int m) {
    return {index / m, index % m};
}

bool correct(const matrix<char> & maze, int i, int j, bool hasKey) {
    int n = static_cast<int>(maze.size());
    int m = static_cast<int>(maze[0].size());
    if (!(0 <= i && i < n) || !(0 <= j && j < m)) {
        return false;
    }

    if (maze[i][j] == '.' || maze[i][j] == 'F' || maze[i][j] == 'S' || maze[i][j] == 'K') {
        return true;
    }

    if (maze[i][j] == 'd' && hasKey == true) {
        return true;
    }

    return false;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<char> maze(n, row<char>(m));
    std::pair<int, int> start, finish, stopper = {-1, -1};
    start = finish = stopper;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> maze[i][j];
            
            if (maze[i][j] == 'S') {
                start = {i, j};
            } else if (maze[i][j] == 'F') {
                finish = {i, j};
            } else if (maze[i][j] == 'D') {
                maze[i][j] = 'd';
            }
        }
    }

    if (start == stopper || finish == stopper) {
        std::cout << "-1\n";
        return 0;
    }

    std::vector<matrix<char>> parents = {maze, maze};
    
    std::queue<std::pair<long long, bool>> BFS;

    BFS.push({pairToInt(start, m), false});
    while (!BFS.empty()) {
        auto [posIndex, hasKey] = BFS.front();
        BFS.pop(); 

        std::pair<int, int> curPos = intToPair(posIndex, m);
        for (int k = 0; k < 4; ++k) {
            std::pair<int, int> tempPos = curPos + offsets[k];
            auto & [i, j] = tempPos;
                if (correct(parents[hasKey], i, j, hasKey)) {
                    parents[hasKey][i][j] = directions[k];
                    BFS.push({pairToInt(tempPos, m), hasKey});
                    if (maze[i][j] == 'K') {
                        parents[true][i][j] = 'P';
                        BFS.push({pairToInt(tempPos, m), true});
                    }

                    if (maze[i][j] == 'F') {
                        std::string path;
                        while (tempPos != start || hasKey == true) {
                            path.push_back(parents[hasKey][i][j]);
                            if (parents[hasKey][i][j] == 'P') {
                                hasKey = false;
                                continue;
                            } else {
                                char direction = reverseDirections[parents[hasKey][i][j]];
                                int offsetIndex = directions.find(direction);
                                tempPos += offsets[offsetIndex];
                            }
                        }
                        std::reverse(path.begin(), path.end());
                        std::cout << path.size() << '\n';
                        std::cout << path << '\n';
                        return 0;
                    }
            }
        }
    }

    std::cout << "-1\n";
    return 0;
}
```
