# Турнир Войн: Испытание Силы

**Ограничение времени:** 1 с  
**Ограничение памяти:** 64.0 Мб  
**Ввод:** стандартный ввод или `input.txt`  
**Вывод:** стандартный вывод или `output.txt`

В далёкой стране, где честь и сила решают всё, собирается великий турнир.  
$ n $ доблестных воинов встают плечом к плечу, образуя **круг**. У каждого из них есть тайная сила — $ a_i $, которая определяет его могущество.

## Правила турнира

- Турнир начинается с **первого воина** (позиция 0 в массиве).
- Каждый раунд: текущий воин вызывает **своих двух ближайших соседей** — слева и справа.
- Эти **три воина** (текущий + левый + правый) участвуют в поединке:
  - Воин с **наименьшей силой** выбывает из круга.
  - Воин с **наибольшей силой** становится **новым текущим** (ведущим следующего раунда).
- Остальные воины сохраняют свои позиции; круг сжимается после выбывания.
- Процесс повторяется, пока в круге **не останется ровно два воина** — они и считаются победителями.

> **Важно:** круг остаётся связным после каждого выбывания, и соседи обновляются динамически.

## Формат входных данных

- Первая строка содержит целое число $ n $ ($ 1 \leq n \leq 2 \cdot 10^5 $) — количество воинов.
- Вторая строка содержит $ n $ **различных** целых чисел $ a_1, a_2, \dots, a_n $ ($ |a_i| \leq 10^9 $) — силы воинов **по кругу**, начиная с текущего и далее **по часовой стрелке**.

## Формат выходных данных

Выведите два целых числа — силы двух оставшихся воинов:

- **Первое число** — сила **текущего воина** на момент завершения (последнего ведущего боя),
- **Второе число** — сила его **единственного соседа** (в круге из двух они друг у друга — единственные соседи).

---

## Пример 1

**Ввод:**
```
5
3 2 5 4 1
```

**Вывод:**
```
4 5
```

## Пример 2

**Ввод:**
```
7
6 2 5 1 7 3 4
```

**Вывод:**
```
7 6
```
## Решение

main.cpp
```cpp
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_map>


struct ListNode {
public:
    ListNode() : val(std::numeric_limits<int>::min()), next(this), prev(this) {}
    ListNode(int x) : val(x), next(this), prev(this) {}
    ListNode(int x, ListNode * nextt) : val(x), next(nextt) {}
    ListNode(int x, ListNode * nextt, ListNode * prevv) : val(x), next(nextt), prev(prevv) {}

    int val;
    ListNode * next;
    ListNode * prev;
};

void trio(ListNode * cur, std::string message = "") {
    std::cout << message << cur->prev->val << ' ' << cur->val << ' ' << cur->next->val << '\n';
    return;
}

int main() {
    int n;
    std::cin >> n;
    int wariorStrength;
    std::cin >> wariorStrength;
    ListNode * curWarior = new ListNode(wariorStrength);
    ListNode * tempWarior = curWarior;

    for (int i = 1; i < n; ++i) {
        std::cin >> wariorStrength;
        ListNode * temp = new ListNode(wariorStrength);
        tempWarior->next = temp;
        temp->prev = tempWarior;
        tempWarior = temp;
    }

    tempWarior->next = curWarior;
    curWarior->prev = tempWarior;

    if (n < 3) {
        std::cout << curWarior->val << ' ' << curWarior->next->val << '\n';
        return 0;
    }

    ListNode * prevWarior;
    while (n > 2) {
        prevWarior = curWarior;

        std::vector<int> strength = {curWarior->prev->val, curWarior->val, curWarior->next->val};
        std::vector<ListNode *> wariors = {curWarior->prev, curWarior, curWarior->next};
        const auto [minIter, maxIter] = std::minmax_element(strength.begin(), strength.end());
        int minIndex = minIter - strength.begin();
        int maxIndex = maxIter - strength.begin();
        if (maxIndex == 0) {
            curWarior = curWarior->prev;
        } else if (maxIndex == 2) {
            curWarior = curWarior->next;
        }

        ListNode * tracker = wariors[minIndex];

        if (tracker == prevWarior) {
            prevWarior = nullptr;
        }

        tracker->prev->next = tracker->next;
        tracker->next->prev = tracker->prev;
        delete tracker;

        --n;
    }

    if (prevWarior != nullptr) {
        std::cout << prevWarior->val << ' ' << prevWarior->next->val << '\n';
    } else {
        std::cout << curWarior->next->val << ' ' << curWarior->val << '\n';
    }

    return 0;
}
```
