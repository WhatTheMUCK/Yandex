#include <iostream>
#include <algorithm>
#include <vector>

template <typename Iter>
void PrintResults(Iter first, Iter last) {
    while (first != last) {
        std::cout << *first << ' ';
        ++first;
    }
    std::cout << '\n';
    return;
}

template <typename T>
void Process(const std::vector<T>& data) {
    std::vector<T> filtered;
    filtered.reserve(data.size());

    auto filteredLast = std::copy_if(
        data.begin(),
        data.end(),
        filtered.begin(),
        [](const T& x) { return x > 0; }
    );

    PrintResults(filtered.begin(), filteredLast);
    return;
}



int main() {
    std::vector<int> data = {1, -1, 2, -2, 3, -3, 4, -4, 5, -5};
    Process(data);
    return 0;
}