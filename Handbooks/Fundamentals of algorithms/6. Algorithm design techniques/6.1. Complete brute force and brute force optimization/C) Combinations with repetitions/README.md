# Сочетания с повторениями

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Выведите число сочетаний с повторениями $\overline{C}(n, k)$.

## Формат ввода

В первой строке находятся два числа $n$ ($1 \leq n \leq 4$), $k$ ($1 \leq k \leq 4$).

## Формат вывода

Выведите ответ на задачу.

## Примеры

### Пример 1

**Ввод:**
```
1 1
```

**Вывод:**
```
1
```

### Пример 2

**Ввод:**
```
4 3
```

**Вывод:**
```
20
```

### Пример 3

**Ввод:**
```
2 2
```

**Вывод:**
```
3
```
## Решение

main.cpp
```cpp
#include <iostream>

long long combinations(int n, int k) {
    if (k > n) {
        return 0;
    }
    
    long long answer = 1;
    long long num = 1, denum = 1;
    for (int i = 1; i <= n; ++i) {
        if (i <= k) {
            denum *= i;
        } 

        if (i > (n - k)) {
            num *= i;
        }
    }
    answer = num / denum;
    return answer;
}


long long combinationsWithRepetition(int n, int k) {
    return combinations(n + k - 1, k);
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::cout << combinationsWithRepetition(n, k) << '\n';
    return 0;
}
```
