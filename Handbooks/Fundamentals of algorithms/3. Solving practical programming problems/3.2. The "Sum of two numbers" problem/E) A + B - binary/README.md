# A + B двоичные

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Даны два числа $ A $ и $ B $, записанные в **двоичной системе счисления** (без ведущих нулей, кроме самого числа `0`).  
Требуется вычислить их сумму и вывести результат также в **двоичной системе**, **без ведущих нулей**.

---

## Формат входных данных

- Первая строка: двоичная строка $ A $.
- Вторая строка: двоичная строка $ B $.

Длины строк не превышают $ 10^5 $.

## Формат выходных данных

Выведите одно двоичное число — сумму $ A + B $ в двоичной системе.

---

## Примеры

### Пример 1

**Ввод:**
```
1011
110
```

**Вывод:**
```
10001
```

### Пример 2

**Ввод:**
```
1111
1
```

**Вывод:**
```
10000
```

## Решение

main.cpp
```cpp
#include <iostream>
#include <algorithm>


int main() {
    std::string A, B;
    std::cin >> A >> B;
    int aIndex = static_cast<int>(A.size()) - 1;
    int bIndex = static_cast<int>(B.size()) - 1;
    std::string answer;
    int acc = 0;
    for (; aIndex >= 0 || bIndex >= 0 || acc; --aIndex, --bIndex) {
        if (aIndex < 0 && bIndex < 0) {
            char curChar = '0' + acc % 2;
            answer.push_back(curChar);
            acc /= 2;
            continue;
        }

        if (aIndex < 0) {
            int cur = B[bIndex] - '0';
            char curChar = '0' + ((acc + cur) % 2);
            answer.push_back(curChar);
            acc = (acc + cur) / 2;
            continue;
        }

        if (bIndex < 0) {
            int cur = A[aIndex] - '0';
            char curChar = '0' + ((acc + cur) % 2);
            answer.push_back(curChar);
            acc = (acc + cur) / 2;
            continue;
        }
        int cur = (A[aIndex] - '0') + (B[bIndex] - '0');
        char curChar = '0' + ((acc + cur) % 2);
        answer.push_back(curChar);
        acc = (acc + cur) / 2;
    }

    std::reverse(answer.begin(), answer.end());
    std::cout << answer << '\n';

    return 0;
}
```
