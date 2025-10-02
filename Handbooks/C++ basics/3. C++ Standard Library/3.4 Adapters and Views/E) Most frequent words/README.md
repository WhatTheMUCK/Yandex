# Самые частотные слова

**Ограничение времени**  
 4 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Выведите `k` самых частотных слов текста и их частоты.

---

### Формат ввода

В первой строке указано натуральное число `k`, не превосходящее 1000.  
Далее идут строки текста объёмом до 1 Мб.  
Слова в тексте разделены пробелами или переводами строк.  
Различать регистр и обрабатывать пунктуацию **не нужно**.

---

### Формат вывода

В выводе должно быть не более `k` самых частотных слов текста.  
Через табуляцию после слова напечатайте его частоту.  
Слова должны быть упорядочены **по убыванию частоты**, а при равенстве частот — **по алфавиту**.

---

### Пример

**Ввод:**
```text
3
to be or not to be
that is the question
```

**Вывод:**
```text
be	2
to	2
is	1
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>


int main() {
    size_t k;
    std::cin >> k;
    std::unordered_map<std::string, int> mp;
    std::string input;
    while (std::cin >> input) {
        ++mp[input];
    }

    std::vector<std::pair<std::string, int>> vec(mp.begin(), mp.end());
    std::sort(vec.begin(), vec.end(), [](const auto & lhs, const auto & rhs){
        return std::tie(rhs.second, lhs.first) < std::tie(lhs.second, rhs.first);
    });

    for (size_t i = 0; i < k && i < vec.size(); ++i) {
        std::cout << vec[i].first << '\t' << vec[i].second << '\n';
    }

    return 0;
}
```
