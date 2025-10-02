# Алгоритм unique  
**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вам надо написать свою реализацию стандартного алгоритма `unique`. Заголовок функции должен быть таким:

```cpp
template <typename Iter>
Iter Unique(Iter first, Iter last);
```

Функция должна переупорядочить элементы диапазона `[first; last)` так, чтобы подряд идущие одинаковые элементы в ней не встречались. Функция возвращает итератор за последний элемент итоговой последовательности. Что останется в пределах от этого вернувшегося итератора до старого `last` — не важно. Время работы функции должно линейно зависеть от длины диапазона.

**Примечание**  
В вашем решении должен быть только код этой шаблонной функции и не должно быть функции `main`. Использовать вызов `std::unique` нельзя.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename Iter>
Iter Unique(Iter first, Iter last) {
    if (first == last) {
        return last;
    }

    Iter prev = first;
    ++first;
    while (first != last) {
        if (*first != *prev) {
            prev = first;
            ++first;
            continue;
        }

        Iter tmp = first;
        Iter tmpPrev = tmp;
        while (++tmp != last) {
            std::swap(*tmp, *tmpPrev);
            tmpPrev = tmp;
        }
        --last;
    }
    return last;
}

int main() {
    std::vector<int> v = {1, 2, 2, 3, 4, 4, 1, 1, 1, 1, 1, 1, 3};
    // std::unique(v.begin(), v.end());
    v.erase(Unique(v.begin(), v.end()), v.end());
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
```
