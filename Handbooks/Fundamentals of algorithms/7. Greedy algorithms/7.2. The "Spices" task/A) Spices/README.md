# Специи

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Вор пробрался в лавку специй и нашёл там $n$ видов специй.  
В его рюкзак можно сложить до $W$ фунтов, поэтому забрать всё он не сможет.

Для каждой специи $i$ известны:
- $w_i$ — количество фунтов этой специи в лавке,
- $c_i$ — общая стоимость всего объёма $w_i$ фунтов.

Вор может взять **любую долю** от каждого вида специй (дробное количество фунтов).  
Если он возьмёт $u_i$ фунтов специи $i$ (где $0 \leq u_i \leq w_i$), то получит ценность:

$$
\frac{c_i}{w_i} \cdot u_i
$$

Общая ценность украденного:

$$
\sum_{i=1}^{n} \frac{c_i}{w_i} \cdot u_i
$$

при ограничении:

$$
\sum_{i=1}^{n} u_i \leq W
$$

Требуется **максимизировать** общую ценность.

> Это классическая задача о **дробном рюкзаке**, решаемая жадным алгоритмом: брать сначала специи с **наибольшей удельной стоимостью** ($c_i / w_i$).

## Формат ввода

- Первая строка содержит два целых числа: $n$ (количество видов специй) и $W$ (вместимость рюкзака).
- Следующие $n$ строк содержат по два целых числа: $c_i$ и $w_i$ — общая стоимость и вес $i$-й специи.

**Ограничения:**
- $1 \leq n \leq 10^3$
- $0 \leq W \leq 2 \cdot 10^6$
- $0 \leq c_i \leq 2 \cdot 10^6$
- $0 < w_i \leq 2 \cdot 10^6$

## Формат вывода

Выведите **максимальную возможную ценность** украденных специй.

Ответ должен быть выведен как **вещественное число** с достаточной точностью.  
Абсолютная погрешность не должна превышать $10^{-3}$.  
Рекомендуется выводить не менее **трёх знаков после запятой**.

## Примеры

### Пример 1

**Ввод:**
```
3 50
60 20
100 50
120 30
```

**Вывод:**
```
180.000
```

### Пример 2

**Ввод:**
```
1 10
500 30
```

**Вывод:**
```
166.667
```

### Пример 3

**Ввод:**
```
1 1000
500 30
```

**Вывод:**
```
500.000
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


int main() {
    int n, W;
    std::cin >> n >> W;
    std::vector<std::pair<int, int>> species(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> species[i].first >> species[i].second;
    }
    std::sort(species.begin(), species.end(), [](const auto & lhs, const auto & rhs){
        return 1ll * lhs.first * rhs.second > 1ll * rhs.first * lhs.second;
    });

    double answer = 0;
    for (size_t curSpeciesIndex = 0; W > 0 && curSpeciesIndex < species.size(); ++curSpeciesIndex) {
        int amount = std::min(W, species[curSpeciesIndex].second);
        W -= amount;
        if (amount == species[curSpeciesIndex].second) {
            answer += species[curSpeciesIndex].first;
        } else {
            answer += amount * ((1.0 * species[curSpeciesIndex].first) / species[curSpeciesIndex].second);
        }
    }
    std::cout << std::fixed << std::setprecision(4) << answer << '\n';

    return 0;
}
```
