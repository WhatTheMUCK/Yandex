#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> sortedVector(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> sortedVector[i];
    }
    for (int i = 0; i < k; ++i) {
        int search;
        std::cin >> search;
        std::vector<int>::iterator it = std::lower_bound(sortedVector.begin(), sortedVector.end(), search);
        if (it == sortedVector.end()) {
            std::cout << *(std::prev(it)) << '\n';
            continue;
        }
        int x1, x2 = *it;
        if (it == sortedVector.begin()) {
            x1 = x2;
        } else {
            x1 = *(std::prev(it));
        }

        if (abs(search - x1) <= abs(search - x2)) {
            std::cout << x1 << '\n';
            continue;
        }

        std::cout << x2 << '\n';
    }
    return 0;
}