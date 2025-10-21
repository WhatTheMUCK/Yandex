# Минимум поворотов

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

На прямоугольной карте размером $n \times m$ есть свободные клетки `.` и стены `#`. Даны стартовая клетка `S` и финишная клетка `F`.  
За один ход можно перейти в одну из четырёх соседних по стороне клеток (вверх, вниз, влево, вправо), если там нет стены.

**Цена пути** — это число поворотов направления при движении от `S` к `F`.  
Первый шаг **не считается поворотом** (направление ещё не задано).

Найдите минимально возможное число поворотов.

## Формат ввода

- Первая строка содержит два целых числа $n$, $m$ ($1 \leq n, m \leq 1000$).
- Далее идут $n$ строк по $m$ символов каждая — карта:
  - `.` — свободная клетка,
  - `#` — стена,
  - `S` — старт,
  - `F` — финиш.

Гарантируется, что `S` и `F` встречаются ровно по одному разу.

## Формат вывода

Выведите одно число — минимальное количество поворотов на пути из `S` в `F`.  
Если пути не существует, выведите `-1`.

## Примеры

### Пример 1

**Ввод**  
```
5 6
S..#..
##..#.
.#..#.
.#....
..#.F.
```

**Вывод**  
```
3
```

### Пример 2

**Ввод**  
```
5 7
S#..#..
.#..#..
..##..#
#...#..
..#..F.
```

**Вывод**  
```
5
```

### Пример 3

**Ввод**  
```
4 4
S#.F
.#..
.###
....
```

**Вывод**  
```
-1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <queue>
#include <limits>

template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[i].size(); ++j) {    
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

template <typename T, typename V>
std::pair<T, V> & operator+=(std::pair<T, V> & lhs, const std::pair<T, V> rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> operator+(std::pair<T, V> lhs, const std::pair<T, V> rhs) {
    return lhs += rhs;
}


std::vector<std::pair<int, int>> offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int offsetsSize = offsets.size();

struct DjkstraState {
    std::pair<int, int> pos;
    long long rotates;
    int curDirection;

    bool operator>(const DjkstraState & other) const {
        return rotates > other.rotates;
    }
};

bool correct(std::pair<int, int> pos, const matrix<char> & map) {
    int n = static_cast<int>(map.size());
    int m = static_cast<int>(map[0].size());
    auto [i, j] = pos;
    if (!(0 <= i && i < n) || !(0 <= j && j < m)) {
        return false;
    }

    if (map[i][j] == '#') {
        return false;
    }

    return true;
}

long long Djkstra(std::pair<int, int> start, std::pair<int, int> finish,
                  const matrix<char> & map) {
    //
    long long infinity = std::numeric_limits<long long>::max();
    std::vector<matrix<long long>> rotates(offsetsSize, matrix<long long>(map.size(), row<long long>(map[0].size(), infinity)));    
    
    auto [startI, startJ] = start;
    std::priority_queue<DjkstraState, std::vector<DjkstraState>, std::greater<DjkstraState>> pq;
    for (int curDirection = 0; curDirection < offsetsSize; ++curDirection) {
        DjkstraState state;
        state.pos = start;
        state.rotates = 0;
        state.curDirection = curDirection;
        rotates[curDirection][startI][startJ] = 0;
        pq.push(state);
    }

    while (!pq.empty()) {
        DjkstraState curState = pq.top();
        pq.pop();

        auto [curI, curJ] = curState.pos;
        if (curState.rotates != rotates[curState.curDirection][curI][curJ]) {
            continue;
        }

        if (curState.pos == finish) {
            return curState.rotates;
        }

        DjkstraState tempState = curState;
        tempState.pos += offsets[curState.curDirection];
        while (correct(tempState.pos, map)) {
            auto [tempI, tempJ] = tempState.pos;
            if (curState.rotates < rotates[tempState.curDirection][tempI][tempJ]) {
                rotates[tempState.curDirection][tempI][tempJ] = curState.rotates;
                pq.push(tempState);
            }
            tempState.pos += offsets[curState.curDirection];
        }

        tempState = curState;
        ++tempState.rotates;
        for (int direction = 0; direction < 4; ++direction) {
            if (direction == curState.curDirection) {
                continue;
            }
            tempState.curDirection = direction;
            auto [tempI, tempJ] = tempState.pos;
            if (tempState.rotates < rotates[tempState.curDirection][tempI][tempJ]) {
                rotates[tempState.curDirection][tempI][tempJ] = tempState.rotates;
                pq.push(tempState);
            }
        }

    }
    
    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    matrix<char> map(n, row<char>(m, '.'));
    matrix<bool> visited(n, row<bool>(m, false));
    std::pair<int, int> start, finish;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> map[i][j];

            if (map[i][j] == 'S') {
                start = {i, j};
                continue;
            }

            if (map[i][j] == 'F') {
                finish = {i, j};
                continue;
            }
        }
    }

    std::cout << Djkstra(start, finish, map) << '\n';
    return 0;
}
```
