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