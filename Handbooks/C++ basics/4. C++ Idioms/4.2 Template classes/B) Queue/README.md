# Queue

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вам требуется реализовать класс `Queue`, аналогичный адаптеру `std::queue`. Он является обёрткой над некоторым стандартным контейнером и реализует интерфейс очереди. Класс должен быть шаблонным.  

Первый шаблонный параметр `T` — тип хранимых элементов.  
Второй шаблонный параметр — контейнер, используемый для хранения элементов (по умолчанию — `std::deque<T>`):

```cpp
template <typename T, typename Container = std::deque<T>>
class Queue;
```

---

### Предусмотрите в классе следующее:

- **Конструктор по умолчанию**, создающий пустую очередь.
- **Константную функцию `front()`**, которая возвращает элемент, стоящий в начале очереди.
- **Неконстантную функцию `front()`**, которая возвращает по ссылке элемент, стоящий в начале очереди — тем самым давая возможность его изменить.
- **Функцию `pop()`**, которая убирает элемент из начала очереди (и ничего не возвращает).
- **Функцию `push()`**, которая кладёт переданный элемент в конец очереди.
- **Функцию `size()`**, которая возвращает количество элементов.
- **Функцию `empty()`**, которая возвращает `true` тогда и только тогда, когда очередь пуста.
- **Операторы `==` и `!=`** для сравнения двух очередей.
## Решение

main.cpp
```cpp
#include <iostream>
#include <deque>
#include <vector>


template <typename T, typename Container = std::deque<T>>
class Queue {
public:
    Queue() = default;
    Queue(Container data) : queue(data) {}

    const T & front() const {
        return *(std::begin(queue));
    }

    T & front() {
        return *(std::begin(queue));
    }

    void pop() {
        // Не у всех стандартных контейнеров есть pop_front()
        queue = Container(std::next(std::begin(queue)), std::end(queue));
        return;
    }

    void push(const T & elem) {
        queue.insert(std::end(queue), elem);
        return;
    }

    size_t size() const {
        return queue.size();
    }

    bool empty() const {
        return queue.empty();
    }

    bool operator==(const Queue<T, Container> & rhs) const {
        return queue == rhs.queue;
    }

private:
    Container queue;
};

template <typename T, typename Container = std::deque<T>>
bool operator!=(const Queue<T, Container> & lhs, const Queue<T, Container> & rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Container = std::deque<T>>
std::ostream & operator<<(std::ostream & os, const Queue<T, Container> & rhs) {
    Queue<T, Container> tmp = rhs;
    while (!tmp.empty()) {
        os << tmp.front() << ' ';
        tmp.pop();
    }
    return os;
}

int main() {
    Queue<double, std::vector<double>> queue;
    std::cout << std::boolalpha << queue.size() << ' ' << queue.empty() << '\n';
    queue.push(3.14);
    std::cout << queue << '\n';
    queue.push(6.28);
    std::cout << queue << '\n';
    queue.pop();
    std::cout << queue << '\n';
    queue.pop();
    std::cout << queue << '\n';
    queue = Queue<double, std::vector<double>>({1, 2, 3, 4, 5});
    std::cout << queue << '\n';
    std::cout << (queue == Queue<double, std::vector<double>>({1, 2, 3, 4, 5})) << '\n';
    std::cout << (Queue<double, std::vector<double>>({1, 2, 3, 4, 5}) == Queue<double, std::vector<double>>({1, 2, 3, 4, 5})) << '\n';
    std::cout << (Queue<double, std::vector<double>>({1, 2, 3, 4, 5}) == Queue<double, std::vector<double>>({2, 3, 3, 4, 5})) << '\n';
    return 0;
}
```
