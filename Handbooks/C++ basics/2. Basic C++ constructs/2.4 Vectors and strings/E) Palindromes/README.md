# Палиндромы

**Ограничение времени**  
1 с

**Ограничение памяти**  
76.4 Мб

**Ввод**  
стандартный ввод или `input.txt`

**Вывод**  
стандартный вывод или `output.txt`

---

Дана строка из строчных латинских букв и пробелов. Проверьте, является ли она палиндромом **без учета пробелов**.

---

## Формат ввода

На вход подается одна строка. В строке могут быть пробелы. Подряд может идти произвольное число пробелов.  
Длина строки не превосходит `100`.

---

## Формат вывода

Представьте, что из строки удалили все пробелы.  
Необходимо вывести `YES`, если полученная строка — палиндром, и `NO` в противном случае.

---

## Пример 1

**Ввод:**
```
hello world
```

**Вывод:**
```
NO
```

---

## Пример 2

**Ввод:**
```
never odd or even
```

**Вывод:**
```
YES
```

---

## Примечание

Пустая строка считается палиндромом.
## Решение

main.cpp
```cpp
#include <iostream>
#include <algorithm>

bool palindrome(std::string & s) {
    int n = s.size();
    if (n < 2) {
        return true;
    }
    int rightIter = n / 2;
    int leftIter = rightIter - (n % 2 == 0 ? 1 : 0);
    for (; 0 <= leftIter && rightIter < n && s[rightIter] == s[leftIter]; --leftIter, ++rightIter);
    return (leftIter == -1 && rightIter == n);
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    std::cout << (palindrome(input) ? "YES" : "NO") << '\n';
}
```
