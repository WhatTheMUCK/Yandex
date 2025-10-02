# Функция `Split`

**Ограничение времени**: 1 с  
**Ограничение памяти**: 64.0 Мб  
**Ввод**: стандартный ввод или `input.txt`  
**Вывод**: стандартный вывод или `output.txt`

---

## Задание

Вам требуется написать функцию со следующим заголовком:

```cpp
std::vector<std::string> Split(const std::string& str, char delimiter);
```

Функция должна вернуть вектор строк, полученный разбиением строки `str` на части по указанному символу-разделителю `delimiter`.

### Правила разбиения:
- Если разделитель встретился **в начале** строки — в начале результата должна быть **пустая строка**.
- Если разделитель встретился **в конце** строки — в конце результата должна быть **пустая строка**.
- Если два разделителя идут **подряд** — между ними должна быть **пустая строка**.
- Для **пустой строки** на входе — вернуть вектор, содержащий **одну пустую строку**.

---

## Примеры

### Пример 1

**Ввод:**
```
What_is_your_name?
_
```

**Вывод:**
```
What
is
your
name?
```

### Пример 2

**Ввод:**
```
13-24--08-11-2014
-
```

**Вывод:**
```
13
24

08
11
2014
```

*(Обратите внимание: между `24` и `08` — пустая строка из-за двух подряд идущих дефисов.)*

---

## Примечание

Подключите необходимые заголовочные файлы и напишите **только код функции `Split`**. Мы скомпилируем решение с нашей функцией `main`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string & str, char delimiter) {
    std::vector<std::string> answer;
    size_t curPos = 0, nextPos = std::string::npos;
    while ((nextPos = str.find(delimiter, nextPos + 1)) != std::string::npos) {
        answer.push_back(str.substr(curPos, nextPos - curPos));
        curPos = nextPos + 1;
    }
    answer.push_back(str.substr(curPos));

    return answer;
}

std::ostream & operator<<(std::ostream & os, const std::vector<std::string> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        os << i << ": " << vec[i] << '\n';
    }
    return os;
}

int main() {
    std::string input;
    char delimiter;
    std::cout << Split("", ' ') << '\n';
    std::cin >> input >> delimiter;
    std::cout << Split(input, delimiter) << '\n';
    return 0;
}
```
