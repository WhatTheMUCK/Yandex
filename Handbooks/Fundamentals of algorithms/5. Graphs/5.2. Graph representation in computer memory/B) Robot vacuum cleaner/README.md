# Робот-пылесос

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Недавно Вы купили робот-пылесос. Через некоторое время Вы заметили баг в поведении пылесоса: иногда пылесос упирается в стенку или мебель. Правда ли пылесос убирает всю комнату? Для ответа на вопрос Вы получили доступ к плану комнаты и последовательности действий пылесоса.

Комната имеет форму прямоугольника $n \times m$ клеток. Каждая клетка либо пустая, либо занятая.

Робот пылесос умеет делать поворот вправо/влево и ехать вперёд. Если в ходе выполнения действий робот-пылесос пытается выехать за границу комнаты (упирается в стенку) или пытается заехать на мебель, то он остаётся на месте.

Изначально робот пылесос находится в пустой клетке $(r, c)$ и повёрнут вверх. Посчитайте количество клеток, которые посетит робот пылесос, включая стартовую.

## Формат ввода

- В первой строке заданы два числа $n$, $m$ — размер комнаты.
- В следующих $n$ строках задан план комнаты.  
  Если $j$-я клетка в $i$-й строке занята, то $s_{i,j} =$ `#`.  
  Если $j$-я клетка в $i$-й строке свободна, то $s_{i,j} =$ `.`.
- Далее даны два числа $r$ и $c$ — стартовое положение робота-пылесоса (нумерация строк и столбцов начинается с 1).
- В следующей строке задано количество действий $q$ робота-пылесоса.
- Далее следует строка длины $q$, задающая действия пылесоса в порядке выполнения:  
  - `L` — поворот налево,  
  - `R` — поворот направо,  
  - `M` — движение вперёд.

## Формат вывода

Количество клеток, которые посетит робот пылесос, включая стартовую.

## Пример

**Ввод**  
```
3 3
###
...
..#
2 2
6
RMLLMM
```

**Вывод**  
```
3
```

## Ограничения

- $1 \leq n, m \leq 1000$
- $1 \leq r \leq n$
- $1 \leq c \leq m$
- $1 \leq q \leq 10^5$
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

std::vector<std::pair<int, int>> offsets = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int curOffsetIndex = 0;

template <typename T, typename V>
std::pair<T, V> & operator+=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first += rhs.first;
    lhs.second += rhs.second;
    return lhs;
}

template <typename T, typename V>
std::pair<T, V> & operator-=(std::pair<T, V> & lhs, const std::pair<T, V> & rhs) {
    lhs.first -= rhs.first;
    lhs.second -= rhs.second;
    return lhs;
}

template <typename T, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<T, V> & rhs) {
    return os << rhs.first << ' ' << rhs.second;
}

void move(char letter, std::pair<int, int> & curPos) {
    int size = static_cast<int>(offsets.size());
    if (letter == 'L') {
        curOffsetIndex = (curOffsetIndex + (size - 1)) % size;
    } else if (letter == 'R') {
        curOffsetIndex = (curOffsetIndex + 1) % size;
    } else if (letter == 'M') {
        curPos += offsets[curOffsetIndex];
    }
}

bool correct(const matrix<char> & room, std::pair<int, int> & curPos) {
    int n = static_cast<int>(room.size());
    int m = static_cast<int>(room[0].size());
    auto & [r, c] = curPos;
    if (!(0 <= r && r < n) || !(0 <= c && c < m) || room[r][c] == '#') {
        return false;
    }
    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    matrix<char> room(n, row<char>(m, '.'));
    matrix<bool> visited(n, row<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> room[i][j];
        }
    }

    std::pair<int, int> curPos;
    int r, c;
    std::cin >> r >> c;
    --r, --c;
    curPos = {r, c};
    visited[r][c] = true;

    int q, answer = 1;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        char curChar;
        std::cin >> curChar;
        // std::cout << curChar << '\n';
        move(curChar, curPos);
        auto & [r, c] = curPos;
        // std::cout << '\t' << r << ' ' << c << '\n';
        if (!correct(room, curPos)) {
            curPos -= offsets[curOffsetIndex];
        }
        // std::cout << '\t' << r << ' ' << c << '\n';
        if (!visited[r][c]) {
            ++answer;
        }
        visited[r][c] = true;
    }

    std::cout << answer << '\n';

    return 0;
}


```
