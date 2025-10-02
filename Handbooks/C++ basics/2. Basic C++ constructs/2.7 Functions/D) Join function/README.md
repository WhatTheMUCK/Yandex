# Функция `Join`

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Вам требуется написать функцию `Join` со следующим заголовком:

```cpp
std::string Join(const std::vector<std::string>& tokens, char delimiter);
```

Функция должна вернуть строку, полученную **склейкой элементов вектора** через указанный разделитель.

### Пример:
```cpp
Join({"What", "is", "your", "name?"}, '_') 
```
должна вернуть строку:
```text
What_is_your_name?
```

---

## Правила:
- Если вектор `tokens` **пустой** — вернуть **пустую строку**.
- Если в векторе **ровно один элемент** — вернуть его **без добавления разделителя**.

---

## Примечание

Подключите необходимые заголовочные файлы и напишите **только код функции `Join`**. Мы скомпилируем решение с нашей функцией `main`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <string>

std::string Join(const std::vector<std::string>& tokens, char delimiter) {
    std::string answer;
    size_t n = tokens.size();
    if (n == 0) {
        return answer;
    }

    for (size_t i = 1; i < n; ++i) {
        answer += tokens[i - 1] + delimiter;
    }

    answer += tokens.back();

    return answer;
}

int main() {
    std::cout << Join({"What", "is", "your", "name?"}, '_') << '\n';
    std::cout << Join({"What"}, '_') << '\n';
    std::cout << Join({}, '_') << '\n';
    return 0;
}
```
