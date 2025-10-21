# Магическое королевство

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В магическом королевстве есть сеть дорог и порталов.  
Королевство изображается в виде прямоугольной карты размером $n \times m$, каждая клетка которой может быть одного из четырёх видов:

- `#` — обычная дорога  
- `X` — город  
- `.` — поле  
- `@` — магический портал  

Клетки с дорогами и порталами связаны между собой, если они являются соседними **по горизонтали, вертикали или диагонали** (то есть 8-связность).  
Кроме того, **все клетки-порталы связаны друг с другом мгновенно**: из любого портала можно попасть в любой другой без ограничений.

Требуется определить, связаны ли **все города** между собой с помощью дорог и порталов.

## Формат входных данных

- В первой строке заданы два числа $n$ и $m$ ($1 \leq n, m \leq 1000$).
- Далее следуют $n$ строк по $m$ символов, описывающих карту.

## Формат выходных данных

- Если все города связаны (то есть из любого города можно добраться до любого другого по дорогам и/или через порталы), выведите:  
  ```
  YES
  ```
- Иначе выведите:  
  ```
  NO k
  ```  
  где $k$ — **минимальное число порталов**, которые нужно построить (в пустых клетках, то есть там, где сейчас `.`), чтобы все города стали связанными.

## Примеры

### Пример 1

**Ввод**  
```
5 7
X##@..#
#.....#
@...@.#
...X#.X
......#
```

**Вывод**  
```
NO 1
```

### Пример 2

**Ввод**  
```
4 4
.X..
....
X###
...#
```

**Вывод**  
```
NO 2
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

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

template <typename T, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<T, V> & rhs) {
    return os << '{' << rhs.first << ", " << rhs.second << '}'; 
}

std::vector<std::pair<int, int>> offsets = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

template <typename T>
bool correct(const matrix<T> & kingdom, int i, int j, matrix<bool> & visited) {

    int n = static_cast<int>(kingdom.size());
    int m = static_cast<int>(kingdom[0].size());

    if (!(0 <= i && i < n) || !(0 <= j && j < m)) {
        return false;
    }

    if (kingdom[i][j] == '.') {
        visited[i][j] = true;
    }

    if (visited[i][j]) {
        return false;
    }

    return true;
}

template <typename T>
void bfs(const matrix<T> & kingdom, int i, int j, matrix<bool> & visited,
        const std::vector<std::pair<int, int>> & portals, bool & portalActivated,
        std::vector<std::vector<std::pair<int, int>>> & components) {

    std::queue<std::pair<int, int>> BFS;
    BFS.push({i, j});
    visited[i][j] = true;
    components.push_back({});
    // std::cout << "Перечислим какие места посетил BFS:\n";
    while (!BFS.empty()) {
        std::pair<int, int> curPos = BFS.front();
        // std::cout << curPos << ' ';
        BFS.pop();

        auto [curI, curJ] = curPos;
        if (kingdom[curI][curJ] == 'X') {
            components.back().push_back({curI, curJ});
        }

        if (kingdom[curI][curJ] == '@' && !portalActivated) {
            portalActivated = true;
            for (std::pair<int, int> portal : portals) {
                auto [portalI, portalJ] = portal;
                if (visited[portalI][portalJ]) {
                    continue;
                }

                visited[portalI][portalJ] = true;
                BFS.push({portalI, portalJ});
            }
        }

        for (std::pair<int, int> offset : offsets) {
            auto [tempI, tempJ] = curPos + offset;
            if (correct(kingdom, tempI, tempJ, visited)) {
                visited[tempI][tempJ] = true;
                BFS.push({tempI, tempJ});
            }
        }
    }
    // std::cout << '\n';
}  

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<char> kingdom(n, row<char>(m, '.'));
    std::vector<std::pair<int, int>> portals, cities;
    matrix<bool> visited(n, row<bool>(m, false));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> kingdom[i][j];
            if (kingdom[i][j] == '@') {
                portals.push_back({i, j});
                continue;
            }

            if (kingdom[i][j] == 'X') {
                cities.push_back({i, j});
                continue;
            }

            if (kingdom[i][j] == '.') {
                visited[i][j] = true;
            }
        }
    }
    
    std::vector<std::vector<std::pair<int, int>>> components;
    bool portalActivated = false;
    for (size_t i = 0; i < cities.size(); ++i) {
        auto [curI, curJ] = cities[i];
        if (visited[curI][curJ]) {
            continue;
        }
        // std::cout << "Начинаем поиск связных городов с "<< cities[i] << '\n';
        bfs(kingdom, curI, curJ, visited, portals, portalActivated ,components);
    }

    if (components.size() == static_cast<size_t>(1)) {
        std::cout << "YES\n";
        return 0;
    }

    int amountOfNeedPortals = static_cast<int>(components.size()) - (!portals.empty());
    std::cout << "NO " << amountOfNeedPortals << '\n';
    // for (size_t i = 0; i < components.size(); ++i) {
    //     std::cout << i << " связность городов:\n  ";
    //     for (const std::pair<int, int> & city : components[i]) {
    //         std::cout << city << ' ';
    //     }
    //     std::cout << '\n';
    // }

    return 0;
}
```
