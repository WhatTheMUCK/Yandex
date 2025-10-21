# Сортировка выбором

**Ограничение времени:** 1 с  
**Ограничение памяти:** 256.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

Реализуйте **сортировку выбором**.

Алгоритм сортировки выбором:
- На каждом шаге находится **минимальный элемент** в неотсортированной части массива.
- Этот элемент **меняется местами** с первым элементом неотсортированной части.
- Процесс повторяется, пока весь массив не будет отсортирован.

## Формат ввода

- В первой строке задано число $n$ ($1 \leq n \leq 1000$).
- Во второй строке задано $n$ целых чисел $a_i$ ($1 \leq a_i \leq 10^9$).

## Формат вывода

Выведите отсортированный по возрастанию массив чисел через пробел.

## Примеры

### Пример 1

**Ввод:**
```
7
13 17 37 73 31 19 23
```

**Вывод:**
```
13 17 19 23 31 37 73
```

### Пример 2

**Ввод:**
```
6
12 18 7 11 5 17
```

**Вывод:**
```
5 7 11 12 17 18
```

### Пример 3

**Ввод:**
```
3
1 2 3
```

**Вывод:**
```
1 2 3
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (i > 0) os << ' ';
        os << rhs[i];
    }
    os << '\n';
    return os;
}

std::vector<int> merge(const std::vector<int> & lhs, const std::vector<int> & rhs) {
    std::vector<int> answer;
    size_t lhsIndex = 0, rhsIndex = 0;
    while (lhsIndex < lhs.size() && rhsIndex < rhs.size()) {
        if (lhs[lhsIndex] <= rhs[rhsIndex]) {
            answer.push_back(lhs[lhsIndex]);
            ++lhsIndex;
        } else {
            answer.push_back(rhs[rhsIndex]);
            ++rhsIndex;
        }
    }

    for (; lhsIndex < lhs.size(); ++lhsIndex) {
        answer.push_back(lhs[lhsIndex]);
    }

    for (; rhsIndex < rhs.size(); ++rhsIndex) {
        answer.push_back(rhs[rhsIndex]);
    }

    return answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> answer(m);
    std::cin >> answer;

    for (int i = 1; i < n; ++i) {
        std::cin >> m;
        std::vector<int> temp(m);
        std::cin >> temp;
        answer = merge(answer, temp);
    }

    std::cout << answer;
    return 0;
}
```
