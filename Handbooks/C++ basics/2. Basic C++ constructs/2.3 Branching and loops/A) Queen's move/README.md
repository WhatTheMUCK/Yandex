# Ход ферзя

## Ограничения

| Параметр             | Значение            |
|----------------------|---------------------|
| Ограничение времени  | 1 секунда           |
| Ограничение памяти   | 64.0 Мб             |
| Ввод                 | стандартный ввод или `input.txt` |
| Вывод                | стандартный вывод или `output.txt` |

---

## Условие задачи

Шахматный ферзь ходит на любое количество клеток по диагонали, горизонтали или вертикали. Даны две различные клетки на шахматной доске без фигур. Определите, может ли ферзь попасть с первой клетки на вторую одним ходом.

### Формат ввода

Программа получает на вход четыре целых числа от 1 до 8. Первая пара чисел задаёт номер столбца и номер строки для первой клетки. Вторая пара чисел аналогично задаёт вторую клетку.

### Формат вывода

Программа должна вывести `YES`, если из первой клетки ходом ферзя можно попасть во вторую, или `NO` в противном случае.

---

### Пример 1

**Ввод:**
```
1
1
2
2
```

**Вывод:**
```
YES
```

---
### Пример 2

**Ввод:**
```
1
1
2
3
```

**Вывод:**
```
NO
```

---
### Пример 3

**Ввод:**
```
5
6
3
3
```

**Вывод:**
```
NO
```

---
## Решение

main.cpp
```cpp
#include <iostream>

struct Position {
    int x, y;
};

std::istream & operator>>(std::istream & is, Position & rhs) {
    return is >> rhs.x >> rhs.y;
}

bool InOneRow(Position & lhs, Position & rhs) {
    return lhs.x == rhs.x;
}

bool InOneCol(Position & lhs, Position & rhs) {
    return lhs.y == rhs.y;
}

bool InOneDiag(Position & lhs, Position & rhs) {
    return std::abs(lhs.x - rhs.x) == std::abs(lhs.y - rhs.y);
}

int main() {
    Position firstPos, secondPos;
    std::cin >> firstPos >> secondPos;
    std::cout << ((InOneRow(firstPos, secondPos) || 
                   InOneCol(firstPos, secondPos) || 
                   InOneDiag(firstPos, secondPos)) ? "YES" : "NO") << '\n';
    return 0;
}
```
