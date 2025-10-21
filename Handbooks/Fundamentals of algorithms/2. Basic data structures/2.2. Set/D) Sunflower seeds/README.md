# Подсолнечник

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Дано семейство множеств $S_1, S_2, \ldots, S_n$.  
Требуется определить, образуют ли они **подсолнечник**: то есть существует такое множество $C$ (**ядро**), что для любых двух различных $i \ne j$ выполняется  
$S_i \cap S_j = C$,  
а **«лепестки»** $P_i = S_i \setminus C$ попарно не пересекаются:  
$P_i \cap P_j = \varnothing$ для всех $i \ne j$.

Если семейство — подсолнечник, выведите `YES`, размер ядра $|C|$ и размеры всех лепестков $|P_1|, |P_2|, \ldots, |P_n|$.  
Иначе выведите `NO`.

## Формат входных данных

Первая строка содержит целое число $n$ ($2 \leq n \leq 2 \cdot 10^5$) — количество множеств.  
Далее следуют $n$ строк: в $i$-й строке сначала дано $k_i$ ($0 \leq k_i \leq 2 \cdot 10^5$) — размер множества, затем $k_i$ различных целых чисел $x$ ($1 \leq x \leq 10^9$) — элементы $S_i$.

Гарантируется, что суммарное число всех элементов $\sum k_i \leq 2 \cdot 10^5$.

## Формат выходных данных

Если семейство — подсолнечник, выведите:

```
YES
```

затем строку с одним числом $|C|$, затем строку из $n$ чисел — $|P_1|, |P_2|, \ldots, |P_n|$.

Иначе выведите:

```
NO
```

## Пример 1

**Ввод**
```
3
3 1 2 3
2 2 3
4 0 2 3 5
```

**Вывод**
```
YES
2
1 0 2
```

## Пример 2

**Ввод**
```
3
2 1 2
2 2 3
2 1 3
```

**Вывод**
```
NO
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> st;
    std::vector<std::unordered_map<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int temp;
            std::cin >> temp;
            if (p[i].contains(temp)) {
                continue;
            }
            ++st[temp];
            ++p[i][temp];
        }
    }
    std::vector<int> c;
    bool canBe = true;
    for (const std::pair<const int, int> & elem : st) {
        if (elem.second == n) {
            c.push_back(elem.first);
            continue;
        }

        if (elem.second != 1) {
            canBe = false;
            break;
        }
    }

    if (!canBe) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n" << c.size() << '\n';
    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        for (int value : c) {
            p[i].erase(value);
        }
        std::cout << p[i].size();
    }
    std::cout << '\n';
    return 0;
}
```
