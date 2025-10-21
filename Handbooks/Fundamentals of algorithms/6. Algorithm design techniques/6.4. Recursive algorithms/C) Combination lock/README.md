# Кодовый замок

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В офисе стоит необычный кодовый замок. Для его открытия нужно ввести секретный код из ровно $K$ цифр.  
Вася выяснил, что код получается из числа $a^b$ — но сам замок принимает **только последние $K$ цифр** этого числа.  
Если у $a^b$ меньше $K$ значащих цифр, то код **дополняется ведущими нулями** до длины $K$.

Ваша задача — определить, какие именно $K$ цифр нужно ввести.

## Формат входных данных

Во входных данных даны три целых числа $a$, $b$, $K$:
- $1 \leq a \leq 10^9$
- $0 \leq b \leq 10^{18}$
- $1 \leq K \leq 18$

## Формат выходных данных

Выведите строку из **ровно $K$ цифр** — последние $K$ цифр числа $a^b$, при необходимости дополняя **ведущими нулями**.

## Примеры

### Пример 1

**Ввод:**
```
2 10 3
```

**Вывод:**
```
024
```

### Пример 2

**Ввод:**
```
7 13 2
```

**Вывод:**
```
07
```
## Решение

iterative.cpp
```cpp
#include <iostream>
#include <algorithm>
__uint128_t MOD = 1;

int main() {
    for (int i = 0; i < 19; ++i) {
        MOD *= 10;
    }

    long long a, b;
    int k;
    std::cin >> a >> b >> k;
    __uint128_t temp = 1;
    for (int i = 63; i >= 0; --i) {
        temp = (temp * temp) % MOD;
        if ((b & (1ll << i)) > 0) {
            temp = (temp * a) % MOD;
        }
    }
    std::string answer;
    while (k > 0) {
        answer.push_back(temp % 10 + '0');
        temp /= 10;
        --k;
    }
    std::reverse(answer.begin(), answer.end());
    std::cout << answer << '\n';
    return 0;
}
```

main.cpp
```cpp
#include <iostream>
#include <string>
#include <algorithm>

using u128 = __uint128_t;

u128 modMult(u128 a, u128 b, u128 mod) {
    return (a * b) % mod;
}

u128 modPow(u128 base, unsigned long long exp, u128 mod) {
    if (exp == 0) return 1 % mod;
    if (exp % 2 == 0) {
        u128 half = modPow(base, exp / 2, mod);
        return modMult(half, half, mod);
    } else {
        return modMult(base, modPow(base, exp - 1, mod), mod);
    }
}

int main() {
    unsigned long long a, b;
    int K;
    std::cin >> a >> b >> K;

    u128 mod = 1;
    for (int i = 0; i < K; ++i) {
        mod *= 10;
    }

    u128 result = modPow(a % mod, b, mod);

    std::string s = "";
    for (int i = 0; i < K; ++i) {
        s += char('0' + (result % 10));
        result /= 10;
    }
    std::reverse(s.begin(), s.end());
    std::cout << s << '\n';
}
```
