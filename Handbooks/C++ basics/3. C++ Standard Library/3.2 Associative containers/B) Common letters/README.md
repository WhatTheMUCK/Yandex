# Общие буквы

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Вам даны слова. Выведите в **алфавитном порядке** список **общих букв**, которые **встречаются в каждом слове**.

---

## Формат ввода

- На вход поступают слова — **по одному в строке**.
- Слова состоят **только из маленьких латинских букв**.
- Длина каждого слова — **не более 100 символов**.
- Количество слов — **не более 1000**.

> 💡 Ввод заканчивается по EOF (конец потока — например, Ctrl+D в Linux или Ctrl+Z в Windows).

---

## Формат вывода

- Выведите **без пробелов** в **алфавитном порядке** все буквы, **присутствующие в каждом слове**.
- Если **общих букв нет** — выведите **пустую строку**.

---

## Пример 1

**Ввод:**
```text
apple
peach
```

**Вывод:**
```text
aep
```

---

## Пример 2

**Ввод:**
```text
alpha
beta
gamma
```

**Вывод:**
```text
a
```

---

## Пример 3

**Ввод:**
```text
alpha
beta
gamma
delta
epsilon
```

**Вывод:**
```text

```

> (пустая строка — общих букв нет)

---

## Примечание

Напишите **полную программу**, читающую из `std::cin` и пишущую в `std::cout`.  
Используйте `std::set` или `std::unordered_set` для отслеживания букв в каждом слове, и пересекайте множества.
## Решение

main.cpp
```cpp
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main() {
    std::string input;
    int amountOfWords = 0;
    std::unordered_map<char, int> mp;
    while (std::cin >> input) {
        std::unordered_set<char> st(input.begin(), input.end());
        for (const char & c : st) {
            ++mp[c];
        }
        ++amountOfWords;
    }
    std::string answer;
    for (const auto & [key, value] : mp) {
        if (value == amountOfWords) {
            answer.push_back(key);
        }
    }
    std::sort(answer.begin(), answer.end());
    std::cout << answer << '\n';
    return 0;
}
```
