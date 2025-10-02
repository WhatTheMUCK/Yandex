# Deque

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

В этой задаче вам надо будет написать свой дек. Писать его по-честному долго и сложно, поэтому мы пошли вам навстречу: вам нужно написать **упрощённую версию дека без итераторов**, умеющую только добавлять элементы в начало и конец. Поддерживать удаление элементов из дека **не требуется**.

В отличие от стандартного дека, возьмите за основу **два вектора**, растущих каждый в свою сторону.

---

### Предлагаемый прототип (вам нужно реализовать указанные функции):

```cpp
#include <cstddef>
#include <vector>

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    bool Empty() const;

    size_t Size() const;

    void Clear();

    const T& operator [] (size_t i) const;

    T& operator [] (size_t i);

    const T& At(size_t i) const;  // throws std::out_of_range on incorrect index

    T& At(size_t i);  // throws std::out_of_range on incorrect index

    const T& Front() const;

    T& Front();

    const T& Back() const;

    T& Back();

    void PushFront(const T& elem);

    void PushBack(const T& elem);
};
```

---

**Примечание**  
Сдайте в систему класс `Deque` с написанными функциями.
## Решение

main.cpp
```cpp
#include <cstddef>
#include <vector>
#include <iostream>

template <typename T>
class Deque {
private:
    std::vector<T> head, tail;

public:
    Deque() = default;
    Deque(const std::vector<T> & input) : tail(input) {}

    bool Empty() const {
        return head.empty() && tail.empty();
    }

    size_t Size() const {
        return head.size() + tail.size();
    }

    void Clear() {
        head.clear(), tail.clear();
        return;
    }

    const T& operator [] (size_t i) const {
        if (i < head.size()) {
            return head[head.size() - (i + 1)];
        }
        return tail[i - head.size()];
    }

    T& operator [] (size_t i) {
        if (i < head.size()) {
            return head[head.size() - (i + 1)];
        }
        return tail[i - head.size()];
    }

    const T& At(size_t i) const { // throws std::out_of_range on incorrect index
        if (i < 0 || i >= Size()) {
            throw std::out_of_range("Incorrect index");
        }

        if (i < head.size()) {
            return head[head.size() - (i + 1)];
        }

        return tail[i - head.size()];
    }

    T& At(size_t i) { // throws std::out_of_range on incorrect index
        if (i < 0 || i >= Size()) {
            throw std::out_of_range("Incorrect index");
        }

        if (i < head.size()) {
            return head[head.size() - (i + 1)];
        }

        return tail[i - head.size()];
    }

    const T& Front() const {
        if (!head.empty())
            return head.back();
        return tail.front();
    }

    T& Front() {
        if (!head.empty())
            return head.back();
        return tail.front();
    }

    const T& Back() const {
        if (!tail.empty())
            return tail.back();
        return head.front();
    }

    T& Back() {
        if (!tail.empty())
            return tail.back();
        return head.front();
    }

    void PushFront(const T& elem) {
        head.push_back(elem);
        return;
    }

    void PushBack(const T& elem) {
        tail.push_back(elem);
        return;
    }

    void Print() {
        for (size_t i = 0; i < head.size(); ++i) {
            std::cout << head[head.size() - (i + 1)] << ' ';
        }

        for (size_t i = 0; i < tail.size(); ++i) {
            std::cout << tail[i] << ' ';
        }
        std::cout << '\n';
        return;
    }
};

int main() {
    Deque<double> deq({1, 2, 3, 4});
    // deq.PushBack(1);
    // deq.PushFront(4);
    // deq.PushFront(3);
    // deq.PushBack(101);
    deq.Print();
    std::cout << "\n[]:\n";
    for (size_t i = 0; i < deq.Size(); ++i) {
        std::cout << deq[i] << '\n';
    }
    std::cout << "\nAt():\n";
    for (size_t i = 0; i < deq.Size(); ++i) {
        std::cout << deq.At(i) << '\n';
    }

    std::cout << std::boolalpha << '\n' << deq.Size() << ' ' << deq.Empty() <<  ' ' << deq.Front() << ' ' << deq.Back() << '\n';

    // std::cout << deq.At(-1) << '\n';
    return 0;
}
```
