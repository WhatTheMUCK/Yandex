# Символьные n-граммы

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Будем называть **символьной n-граммой** — последовательность из `n` **последовательно идущих символов** в одном слове.

Для данного числа `n` подсчитайте **суммарное количество вхождений каждой n-граммы** во всех словах текста.

---

## Формат ввода

- В первой строке: два числа:
  - `m` — количество слов (от 1 до 100000),
  - `n` — длина n-граммы (от 1 до 5).
- Затем — `m` слов, разделённых пробелами или переводами строк.
- **Пунктуацию и регистр обрабатывать не нужно** — читайте слова через `std::cin >> word`.

---

## Формат вывода

Выведите все n-граммы:

- **Отсортированные по убыванию частоты**.
- При **равных частотах** — **в лексикографическом порядке (по алфавиту)**.
- Для каждой n-граммы выведите:
```
<ngram> - <частота>
```

---

## Пример

**Ввод:**
```text
6 2
to be or not to be
```

**Вывод:**
```text
be - 2
to - 2
no - 1
or - 1
ot - 1
```

---

## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

int main() {
    int m, n;
    std::cin >> m >> n;
    std::unordered_map<std::string, int> mp;
    std::string input;
    for (int i = 0; i < m; ++i) {
        std::cin >> input;
        for (int i = 0; i < static_cast<int>(input.size()) - (n - 1); ++i) {
            ++mp[input.substr(i, n)];
        }
    }

    std::vector<std::pair<std::string, int>> vec(mp.begin(), mp.end());
    std::sort(vec.begin(), vec.end(), [](const auto & lhs, const auto & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first);
    });

    for (const auto & [key, value] : vec) {
        std::cout << key << " - " << value << '\n';
    }

    return 0;
}
```
