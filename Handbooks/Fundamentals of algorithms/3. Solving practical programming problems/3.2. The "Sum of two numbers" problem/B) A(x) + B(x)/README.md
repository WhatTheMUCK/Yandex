# A(x) + B(x)

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Необходимо вычислить сумму двух многочленов:

- $ A(x) = a_n \cdot x^n + \dots + a_1 \cdot x + a_0 $,
- $ B(x) = b_m \cdot x^m + \dots + b_1 \cdot x + b_0 $.

Результат — многочлен $ C(x) = A(x) + B(x) $.

---

## Формат ввода

- Первая строка: целое число $ n $ ($ 0 \leq n \leq 10 $).
- Вторая строка: $ n+1 $ целых чисел $ a_n, a_{n-1}, \dots, a_0 $, где $ -100 \leq a_i \leq 100 $, и $ a_n \ne 0 $.
- Третья строка: целое число $ m $ ($ 0 \leq m \leq 10 $).
- Четвёртая строка: $ m+1 $ целых чисел $ b_m, b_{m-1}, \dots, b_0 $, где $ -100 \leq b_i \leq 100 $, и $ b_m \ne 0 $.

> **Гарантия:** старший коэффициент результата ненулевой: $ a_n + b_m \ne 0 $ (если степени равны), либо старший коэффициент более высокой степени не обнуляется.

---

## Формат вывода

- Первая строка: степень $ k $ многочлена $ C(x) = A(x) + B(x) $.
- Вторая строка: $ k+1 $ коэффициентов $ c_k, c_{k-1}, \dots, c_0 $ — коэффициенты суммы.

---

## Примеры

### Пример 1

**Ввод:**
```
3
1 2 3 4
2
1 0 0
```

**Вывод:**
```
3
1 3 3 4
```

### Пример 2

**Ввод:**
```
0
1
9
1 2 3 4 5 6 7 8 9 0
```

**Вывод:**
```
9
1 2 3 4 5 6 7 8 9 1
```

### Пример 3

**Ввод:**
```
1
1 1
1
1 1
```

**Вывод:**
```
1
2 2
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>


int myFront(std::deque<int> & dq) {
    if (dq.empty()) {
        return 0;
    }

    int answer = dq.front();
    dq.pop_front();
    return answer;
}

int main() {
    std::deque<int> A, B;
    int n, m;
    std::cin >> n;
    for (int i = 0; i <= n; ++i) {
        int a;
        std::cin >> a;
        A.push_front(a);
    }

    std::cin >> m;
    for (int i = 0; i <= m; ++i) {
        int b;
        std::cin >> b;
        B.push_front(b);
    }

    std::vector<int> answer;
    while (!A.empty() || !B.empty()) {
        int cur = myFront(A) + myFront(B);
        answer.push_back(cur);
    }
    std::reverse(answer.begin(), answer.end());

    std::cout << answer.size() - 1 << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}
```
