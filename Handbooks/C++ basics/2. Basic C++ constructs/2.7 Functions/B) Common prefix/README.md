# Общий префикс

**Ограничение времени**  
1 с

**Ограничение памяти**  
64.0 Мб

**Ввод**  
стандартный ввод или `input.txt`

**Вывод**  
стандартный вывод или `output.txt`

---

Напишите функцию для вычисления наибольшего общего префикса строк, переданных в векторе `words`:

```
std::string CommonPrefix(const std::vector<std::string>& words);
```

Например, для пустого вектора функция должна вернуть пустую строку, а для вектора из строк `"apple"`, `"apricot"` и `"application"` — строку `"ap"`.

---

## Примечание

В решении не должно быть функции `main`: она будет в нашей тестирующей программе.  
Подключите необходимые библиотеки и напишите код функции `CommonPrefix`.
## Решение

main.cpp
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string CommonPrefix(const std::vector<std::string>& words) {
    std::string answer;

    if (words.empty()) {
        return answer;
    }

    std::vector<std::string>::const_iterator minSize = std::min_element(words.begin(), words.end(), 
    [](const std::string & lhs, const std::string & rhs){
        return lhs.size() < rhs.size();
    }); 

    for (size_t i = 0; i < minSize->size(); ++i) {
        if (std::any_of(words.begin(), words.end(), [&words, i](const std::string & str){ 
            return str[i] != words.front()[i]; 
        })) {
            break;
        }
        answer.push_back(words.front()[i]);
    }
    return answer;
}

int main() {
    std::cout << CommonPrefix({"apple", "apricot", "application"}) << '\n';
    return 0;
}
```
