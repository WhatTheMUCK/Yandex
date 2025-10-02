#include <iostream>
#include <vector>
#include <list>

template <typename Container>
void Print(const Container & data, const std::string & delimiter) {
    std::string answer;
    for (auto cur = std::begin(data); cur != std::end(data); ++cur) {
        std::cout << *cur;
        if (std::next(cur) == std::end(data)) {
            std::cout << '\n';
            break;
        }
        std::cout << delimiter;
    }
    return;
}

int main() {
    // std::vector<int> data = {1, 2, 3, 4};
    // double data[] = {1.2, 2., 3.7, 4.5};
    std::list<int> data = {90, 1, 2, 3};
    Print(data, ", ");  // 1, 2, 3, 4
    return 0;
}