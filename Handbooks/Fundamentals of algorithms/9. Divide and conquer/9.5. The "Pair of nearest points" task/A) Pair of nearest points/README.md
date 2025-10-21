# Ближайшие точки

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Заданы $n$ точек на плоскости с целочисленными координатами.  
Требуется найти **минимальное евклидово расстояние** между любой парой различных точек.

Расстояние между точками $(x_1, y_1)$ и $(x_2, y_2)$ вычисляется по формуле:
$$
\sqrt{(x_1 - x_2)^2 + (y_1 - y_2)^2}
$$

## Формат ввода

- Первая строка: целое число $n$ — количество точек.  
- Следующие $n$ строк: по два целых числа $x_i$, $y_i$ — координаты $i$-й точки.

**Ограничения:**  
$2 \leq n \leq 10^5$,  
$-10^9 \leq x_i, y_i \leq 10^9$.

## Формат вывода

Выведите одно вещественное число — **минимальное расстояние** между двумя точками.

**Требования к точности:**
- Абсолютная погрешность не должна превышать $10^{-5}$.
- Выводите **ровно шесть цифр после десятичной точки** (например, `5.000000`, `1.414214`).

## Примеры

### Пример 1

**Ввод:**
```
2
0 0
3 4
```

**Вывод:**
```
5.000000
```

### Пример 2

**Ввод:**
```
11
4 4
-2 -2
-3 -4
-1 3
2 3
-4 0
1 1
-1 -1
3 -1
-4 2
-2 4
```

**Вывод:**
```
1.414214
```

### Пример 3

**Ввод:**
```
3
0 0
1 1
0 0
```

**Вывод:**
```
0.000000
```

## Примечание

- Если в наборе есть **совпадающие точки**, минимальное расстояние равно `0.000000`.
- Для эффективного решения при больших $n$ рекомендуется использовать **алгоритм «разделяй и властвуй»** за $O(n \log n)$, так как полный перебор ($O(n^2)$) не уложится в ограничение по времени при $n = 10^5$.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

struct Point {
    long long x, y;
    Point() {}
    Point(long long x, long long y) : x(x), y(y) {}
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

double dist(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Слияние двух отсортированных по y массивов
void merge_by_y(vector<Point>& points, int left, int mid, int right, vector<Point>& temp) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (points[i].y <= points[j].y) {
            temp[k++] = points[i++];
        } else {
            temp[k++] = points[j++];
        }
    }
    while (i <= mid) temp[k++] = points[i++];
    while (j <= right) temp[k++] = points[j++];
    for (int idx = left; idx <= right; ++idx) {
        points[idx] = temp[idx];
    }
}

// Рекурсивная функция: возвращает минимальное расстояние
// points[left..right] отсортированы по x
// но в процессе рекурсии мы поддерживаем, что подмассив отсортирован по y
double closest_pair(vector<Point>& points, int left, int right, vector<Point>& temp) {
    if (left >= right) {
        return numeric_limits<double>::max();
    }
    if (left + 1 == right) {
        // Две точки
        double d = dist(points[left], points[right]);
        // Убедимся, что они отсортированы по y
        if (points[left].y > points[right].y) {
            swap(points[left], points[right]);
        }
        return d;
    }

    int mid = (left + right) / 2;
    long long mid_x = points[mid].x;

    // Разделим, но сначала скопируем левую и правую части во временный массив для сортировки по y
    // Рекурсивно решаем левую и правую части
    double d1 = closest_pair(points, left, mid, temp);
    double d2 = closest_pair(points, mid + 1, right, temp);
    double d = min(d1, d2);

    // Слияние по y (чтобы points[left..right] был отсортирован по y)
    merge_by_y(points, left, mid, right, temp);

    // Собираем точки, лежащие в полосе |x - mid_x| < d
    vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (abs(points[i].x - mid_x) < d) {
            strip.push_back(points[i]);
        }
    }

    // Проверяем каждую точку со следующими (до 7)
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
            double d_ij = dist(strip[i], strip[j]);
            if (d_ij < d) {
                d = d_ij;
            }
        }
    }

    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    // Проверка на дубликаты: если есть — ответ 0.0
    sort(points.begin(), points.end());
    for (int i = 1; i < n; ++i) {
        if (points[i].x == points[i-1].x && points[i].y == points[i-1].y) {
            cout << fixed << setprecision(6) << 0.0 << '\n';
            return 0;
        }
    }

    // Подготовка: сортируем по x
    // (уже отсортированы выше, но убедимся)
    // Создаём временный массив для слияния по y
    vector<Point> temp(n);

    double ans = closest_pair(points, 0, n - 1, temp);

    cout << fixed << setprecision(6) << ans << '\n';

    return 0;
}
```
