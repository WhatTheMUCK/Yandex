# Сортировка точек

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Вам даны координаты точек на плоскости. Выведите эти точки в порядке **возрастания расстояний до начала координат**.

---

## Формат ввода

- Сначала задано количество точек `n`.
- Затем идет последовательность из `n` строк, каждая из которых содержит два целых числа — координаты точки `(x, y)`.
- `n` не превосходит `100`.
- Координаты точек по модулю не превосходят `1000`.

---

## Формат вывода

Выведите через пробел координаты точек в порядке возрастания расстояний до начала координат.  
После каждой пары координат печатайте перевод строки.

---

## Пример

**Ввод:**
```text
2
2 3
1 2
```

**Вывод:**
```text
1 2
2 3
```

---

> 💡 Расстояние до начала координат вычисляется по формуле:  
> `d = sqrt(x² + y²)` — но для сортировки можно сравнивать квадраты расстояний, чтобы избежать операций с плавающей точкой.

---

## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int SquareDistance() const {
        return x * x + y * y;
    }

    int x, y;
};

bool operator<(const Point & lhs, const Point & rhs) {
    return lhs.SquareDistance() < rhs.SquareDistance();
}

std::istream & operator>>(std::istream & is, Point & point) {
    return is >> point.x >> point.y;
}

std::ostream & operator<<(std::ostream & os, const Point & point) {
    return os << point.x << ' ' << point.y;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<Point> vec(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    for (size_t i = 0; i < n; ++i) {
        std::cout << vec[i] << '\n';
    }
    return 0;
}
```
