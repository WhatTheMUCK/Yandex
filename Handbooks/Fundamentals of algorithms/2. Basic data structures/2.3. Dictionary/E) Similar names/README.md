# Похожие названия

**Ограничение времени:** 2 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Пара слов **интересная**, если слова отличаются **ровно в одной букве**.

Дан набор слов **одинаковой длины**. Вычислите количество интересных пар.

## Формат ввода

Первая строка содержит одно число $n$ — количество слов.

Далее следуют $n$ строк, каждая содержит ровно одну непустую строку, состоящую из **не более чем 10 символов** английского алфавита. Символы могут быть **верхнего и нижнего регистра**.

## Формат вывода

Вывод должен содержать одно число — количество интересных пар слов.

## Пример 1

**Ввод**
```
5
rom
bom
dom
bot
rot
```

**Вывод**
```
6
```

## Пример 2

**Ввод**
```
3
aa
aa
aa
```

**Вывод**
```
0
```

## Пример 3

**Ввод**
```
6
aaa
aaB
aBa
Baa
BBB
abb
```

**Вывод**
```
3
```

## Примечание

**Ограничения:**  
$1 \leq n \leq 10^5$
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::unordered_map<std::string, long long> freq;
    std::string word;
    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        ++freq[word];
    }

    std::unordered_map<std::string, long long> totalForMask;
    std::unordered_map<std::string, long long> sumSqForMask;

    for (const auto & [w, cnt] : freq) {
        std::string s = w;
        for (size_t i = 0; i < s.size(); ++i) {
            char orig = s[i];
            s[i] = '*';
            totalForMask[s] += cnt;
            sumSqForMask[s] += cnt * cnt;
            s[i] = orig;
        }
    }

    long long answer = 0;
    for (const auto& [mask, total] : totalForMask) {
        const long long & sum_sq = sumSqForMask[mask];
        answer += (total * total - sum_sq) / 2;
    }

    std::cout << answer << '\n';
    return 0;
}
```
