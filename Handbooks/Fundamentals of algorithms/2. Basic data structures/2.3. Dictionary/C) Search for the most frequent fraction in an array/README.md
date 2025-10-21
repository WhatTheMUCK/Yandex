# Поиск самой частой дроби в массиве

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дан массив $a$, состоящий из $n$ дробей.

Необходимо найти такую дробь $x$, значение которой встречается наибольшее количество раз в $a$.  
Если несколько дробей встречаются одинаковое количество раз, выведите **наименьшую** (в смысле числового значения).

## Формат ввода

Первая строка содержит единственное число $n$ — количество дробей в массиве.

Далее идут $n$ строк, каждая из которых содержит по два разделённых пробелом числа $num_i$, $den_i$, где $num_i$ и $den_i$ — числитель и знаменатель $i$-й дроби соответственно.

Среди дробей могут встречаться неправильные и сократимые.

**Ограничения:**  
$1 \leq n \leq 10^3$;  
$1 \leq num_i, den_i \leq 10^3$ для всех $1 \leq i \leq n$.

## Формат вывода

Выведите числитель `numerator` и знаменатель `denominator` **несократимой** дроби $x$, значение которой встречается наибольшее количество раз.

## Пример 1

**Ввод**
```
5
1 2
1 3
2 4
12 24
2 6
```

**Вывод**
```
1 2
```

## Пример 2

**Ввод**
```
5
1 2
1 3
2 4
12 36
2 6
```

**Вывод**
```
1 3
```

## Пример 3

**Ввод**
```
5
1 1
1 5
1 2
1 4
1 3
```

**Вывод**
```
1 5
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <numeric>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


int main() {
    int n;
    std::cin >> n;
    int maxFreq = 0;
    std::pair<int, int >answer = std::numeric_limits<std::pair<int, int>>::max();
    std::unordered_map<std::pair<int, int>, int, PairHash> mp;
    for (int i = 0; i < n; ++i) {
        int num, denum;
        std::cin >> num >> denum;
        int gcd = std::gcd(num, denum);
        num /= gcd;
        denum /= gcd;
        std::pair<int, int> number = {num, denum};
        ++mp[number];
        if (maxFreq <= mp[number]) {
            if (maxFreq == mp[number] && number.first * answer.second >= answer.first * number.second) {
                continue;
            }
            answer = number;
            maxFreq = mp[number];
        }
    }

    std::cout << answer.first << ' ' << answer.second << '\n';

    return 0;
}
```
