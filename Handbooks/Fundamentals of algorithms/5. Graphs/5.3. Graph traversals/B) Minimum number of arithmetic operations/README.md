# Минимальное количество арифметических операций

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Задано число $X$.

Возможны следующие преобразования с числом:

- $X = X + c$, где $c$ — цифра (от 0 до 9),
- $X = X - c$, где $c$ — цифра (от 0 до 9),
- $X = X \cdot c$, где $c$ — цифра (от 0 до 9).

Обратите внимание, $c$ может принимать значение, равное 0.

Необходимо найти минимальное количество операций, которые необходимо применить к числу $X$, чтобы получить число $Y$.

## Формат ввода

В первой строке заданы два числа $X$, $Y$.

## Формат вывода

В единственной строке выведите ответ на задачу.

## Примеры

### Пример 1

**Ввод**  
```
10 1000
```

**Вывод**  
```
3
```

### Пример 2

**Ввод**  
```
2 1
```

**Вывод**  
```
1
```

### Пример 3

**Ввод**  
```
100000 1
```

**Вывод**  
```
2
```

## Ограничения

$$
1 \leq X, Y \leq 10^5
$$
## Решение

main.cpp
```cpp
#include <iostream>
#include <queue>
#include <unordered_set>

const int MAX_VALUE = 200'000;

int main() {
    int x, y;
    std::cin >> x >> y;
    if (x == y) {
        std::cout << "0\n";
        return 0;
    }
    
    std::queue<std::pair<int, int>> BFS;
    std::unordered_set<long long> visited;
    std::string digits = "0123456789";

    BFS.push({x, 0});
    while (!BFS.empty()) {
        auto [parent, steps] = BFS.front();
        BFS.pop();

        ++steps;

        for (char digit : digits) {
            std::vector<long long> curVariants = {
                parent + (digit - '0'),
                parent - (digit - '0'),
                parent * (digit - '0')
            };
            for (long long variant : curVariants) {
                if (variant < 0 || variant > MAX_VALUE) {
                    continue;
                }

                if (visited.contains(variant)) {
                    continue;
                }

                if (variant == y) {
                    std::cout << steps << '\n';
                    return 0;
                }

                visited.insert(variant);
                BFS.push({variant, steps});
            }
        }
    }

    return 0;
}
```
