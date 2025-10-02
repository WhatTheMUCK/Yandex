# Работа склада

**Ограничение времени**  
 25 с  
**Ограничение памяти**  
 1000.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вы работаете оператором на складе. Время от времени вам привозят новые коробки. Каждая коробка имеет свою грузоподъемность `w_i` и объем `v_i`. Получая новую коробку, вы ставите на ней серийный номер, используя все целые неотрицательные числа последовательно, начиная с нуля.

Иногда вас просят выдать коробку **минимальной грузоподъемности**, чтобы она выдержала предмет весом `w` — или коробку **минимальной вместимости**, в которую можно насыпать песок объемом `v`. Вам нужно быстро определять серийный номер коробки, которая будет выдана. Коробки обратно на склад не возвращаются. Если подходящих коробок несколько, нужно выбрать ту, которая **пролежала на складе меньше** (т.е. имеет меньший серийный номер).

---

### Требуется реализовать класс `Stock`, у которого должны быть следующие функции:

- `void Add(int w, int v);` — добавить коробку на склад;
- `int GetByW(int min_w);` — вернуть номер коробки с грузоподъемностью **не меньше** `min_w`;
- `int GetByV(int min_v);` — вернуть номер коробки с объемом **не меньше** `min_v`.

Если подходящей коробки нет, соответствующая функция должна вернуть `-1`.

---

### Примечание

Обратите внимание, что вам нужно отправить **только ваш класс `Stock`**, без функции `main`. Не забудьте, что необходимые функции-члены должны быть доступны вне класса.
## Решение

main.cpp
```cpp
#include <iostream>
#include <set>
#include <unordered_map>

struct CompareByFirstThenBySecondDesc {
    bool operator()(const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) const {
       return std::tie(lhs.first, rhs.second) < std::tie(rhs.first, lhs.second); 
    }
};

class Stock {
public:
    void Add(int w, int v) {
        int curIndex = nextIndex++;
        sortedW.insert({w, curIndex});
        sortedV.insert({v, curIndex});
        indexToWV[curIndex] = {w, v};
    }

    int GetByW(int min_w) {
        auto itW = sortedW.lower_bound({min_w, nextIndex});
        if (itW == sortedW.end()) {
            return -1;
        }

        auto [_, index] = *itW;
        sortedW.erase(itW);
        sortedV.erase({indexToWV[index].second, index});
        return index;
    }

    int GetByV(int min_v) {
        auto itV = sortedV.lower_bound({min_v, nextIndex});
        if (itV == sortedV.end()) {
            return -1;
        }

        auto [_, index] = *itV;
        sortedV.erase(itV);
        sortedW.erase({indexToWV[index].first, index});
        return index;
    }

    void PrintInfo() {
        std::cout << "sortedW:";
        for (const auto & elem : sortedW) {
            std::cout << " {" << elem.first << ", " << elem.second << "}";
        }
        std::cout << "\n";

        std::cout << "sortedV:";
        for (const auto & elem : sortedV) {
            std::cout << " {" << elem.first << ", " << elem.second << "}";
        }
        std::cout << "\n\n";
    }

private:
    int nextIndex = 0;
    std::set<std::pair<int, int>, CompareByFirstThenBySecondDesc> sortedW, sortedV;
    std::unordered_map<int, std::pair<int, int>> indexToWV;
};

int main() {
    Stock st;
    int n = 10;
    for (int i = 0; i < n; ++i) {
        st.Add(n - i, n - i);
    }

    st.Add(5, 10);
    st.Add(10, 5);
    st.Add(5, 10);
    st.Add(10, 5);

    st.PrintInfo();

    for (int i = 0; i < n; ++i) {
        std::cout << "i = " << i << ": " << st.GetByW(5) << ' ' << st.GetByV(5) << '\n';
        st.PrintInfo();
    }

    return 0;
}
```
