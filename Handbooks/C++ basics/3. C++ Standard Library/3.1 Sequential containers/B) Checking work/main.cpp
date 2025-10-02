#include <iostream>
#include <deque>
#include <vector>


int main() {
    int N;
    std::cin >> N;
    std::string surname, direction;
    std::deque<std::string> deq;
    for (int i = 0; i < N; ++i) {
        std::cin >> surname >> direction;
        direction == "top" ? deq.push_front(surname) : deq.push_back(surname);
    }

    std::vector<std::string> notebooks(deq.begin(), deq.end());

    int M, number;
    std::cin >> M;
    for (int i = 0; i < M; ++i) {
        std::cin >> number;
        std::cout << notebooks[number - 1] << '\n';
    }

    return 0;
}