# Числа Фибоначчи

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дано целое число $ n $. Требуется вычислить $ n $-е число Фибоначчи.

## Определение

Числа Фибоначчи задаются рекуррентно:

- $ F_0 = 0 $
- $ F_1 = 1 $
- $ F_n = F_{n-1} + F_{n-2} $, для $ n \geq 2 $

---

## Формат ввода

Целое число $ n $ ($ 0 \leq n \leq 45 $).

## Формат вывода

Выведите одно целое число — $ F_n $.

---

## Примеры

### Пример 1

**Ввод:**
```
3
```

**Вывод:**
```
2
```

### Пример 2

**Ввод:**
```
10
```

**Вывод:**
```
55
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>

std::unordered_map<int, long long> memoization;

long long fibonachi(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    if (memoization.contains(n)) {
        return memoization[n];
    }

    memoization[n] = fibonachi(n - 1) + fibonachi(n - 2);
    return memoization[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << fibonachi(n) << '\n';
    return 0;
}
```
