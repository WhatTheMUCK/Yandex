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