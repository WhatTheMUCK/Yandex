# Сортировка по убыванию

**Ограничение времени**  
1 с

**Ограничение памяти**  
64.0 Мб

**Ввод**  
стандартный ввод или `input.txt`

**Вывод**  
стандартный вывод или `output.txt`

---

Вам даны строки текстового файла. Отсортируйте набор этих строк **по убыванию**.

---

## Формат ввода

Количество строк не превосходит `1000`.  
Каждая строка состоит из символов ASCII с кодами от `32` до `126`, длина строки не превосходит `100`.

---

## Формат вывода

Напечатайте строки в **отсортированном по убыванию порядке**.  
Для сравнения строк друг с другом достаточно использовать стандартные операторы сравнения, определённые для `std::string`.

---

## Пример

**Ввод:**
```
one
two
three
```

**Вывод:**
```
two
three
one
```

---

## Примечание

Компилятор не поддерживает `std::ranges`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> container;
    std::string temp;   
    while (std::getline(std::cin, temp)) {
        container.push_back(temp);
    }
    std::sort(container.begin(), container.end(), std::greater<std::string>());
    for (const std::string & elem : container) {
        std::cout << elem << '\n';
    }
    return 0;
}
```
