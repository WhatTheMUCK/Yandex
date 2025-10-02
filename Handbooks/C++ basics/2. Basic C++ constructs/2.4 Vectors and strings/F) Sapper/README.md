# Сапёр

**Ограничение времени**  
1 с

**Ограничение памяти**  
64.0 Мб

**Ввод**  
стандартный ввод или `input.txt`

**Вывод**  
стандартный вывод или `output.txt`

---

Вам необходимо построить поле для игры «Сапёр» по его конфигурации — высоте, ширине и координатам расставленных на нём мин.

Вкратце напомним правила построения поля для игры «Сапёр»:

- поле состоит из клеток с минами и пустых клеток;
- клетки с миной обозначаются символом `*`;
- пустые клетки содержат число от `0` до `8` — количество мин на соседних клетках.

---

## Формат ввода

В первой строке содержатся три числа:

- число `m` от `1` до `100` — количество строк на поле;
- число `n` от `1` до `100` — количество столбцов на поле;
- число `k` от `0` до `m×n` — количество мин на поле.

В следующих `k` строках содержатся пары чисел с координатами мин (номерами строки и столбца). Нумерация ведётся с единицы.

---

## Формат вывода

Выведите построенное поле, разделяя строки поля символом `\n`, а столбцы — пробелом.

---

## Пример

**Ввод:**
```
3 2 2
1 1
2 2
```

**Вывод:**
```
* 2
2 *
1 1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

struct Position {
    Position() : row_(0), col_(0) {}
    Position(int row, int col) : row_(row), col_(col) {}
    Position & operator+=(const Position & rhs);

    int row_, col_;
};

Position & Position::operator+=(const Position & rhs) {
    this->row_ += rhs.row_;
    this->col_ += rhs.col_;
    return *this;
}

Position operator+(Position lhs, const Position & rhs) {
    return (lhs += rhs);
}

std::istream & operator>>(std::istream & is, Position & pos) {
    return is >> pos.row_ >> pos.col_;
}

std::ostream & operator<<(std::ostream & os, const Position & pos) {
    return os << '(' << pos.row_ << ", " << pos.col_ << ')';
}


int main() {
    int m, n, k;
    std::cin >> m >> n >> k;
    std::vector<std::vector<char>> field(m + 2, std::vector<char>(n + 2, '0'));
    for (int i = 0; i < k; i++) {
        Position tempPos;
        std::cin >> tempPos;
        field[tempPos.row_][tempPos.col_] = '*'; 
    }

    std::vector<Position> offset = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};   
    for (int row = 1; row <= m; ++row) {
        for (int col = 1; col <= n; ++col) {
            if (field[row][col] == '*') {
                continue;
            }

            for (Position & curOffset : offset) {
                Position curPos = Position(row, col) + curOffset; 
                field[row][col] += (field[curPos.row_][curPos.col_] == '*'); 
            }
        }
    }

    for (int row = 1; row <= m; ++row) {
        for (int col = 1; col <= n; ++col) {
            std::cout << field[row][col] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
```
