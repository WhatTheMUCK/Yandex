# Наименьшее общее кратное

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Для двух чисел $a$ и $b$ найдите их наименьшее общее кратное.

## Формат ввода

Целые числа $a$ и $b$ (разделённые пробелом).

**Ограничения:**  
$$
1 \leq a, b \leq 2 \cdot 10^9
$$

## Формат вывода

Наименьшее общее кратное чисел $a$ и $b$.

## Примеры

### Пример 1

**Ввод**  
```
6 8
```

**Вывод**  
```
24
```

### Пример 2

**Ввод**  
```
761457 614573
```

**Вывод**  
```
467970912861
```
## Решение

main.cpp
```cpp
#include <iostream>

template <typename T>
T GCD(T lhs, T rhs) {
    if (lhs < rhs) {
        std::swap(lhs, rhs);
    }

    if (rhs == 0) {
        return lhs;
    }

    return GCD(lhs % rhs, rhs);
}

template <typename T>
T LCM(T lhs, T rhs) {
    return lhs * rhs / GCD(lhs, rhs);
}

int main() {
    long long a, b;
    std::cin >> a >> b;
    std::cout << LCM(a, b) << '\n';
    return 0;
}
```
