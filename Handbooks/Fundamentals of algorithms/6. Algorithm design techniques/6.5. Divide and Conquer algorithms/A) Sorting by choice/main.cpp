#include <iostream>
#include <vector>


void sortingByChoice(std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        int minIndex = i;
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[minIndex]) {
                minIndex = j;
            }
        }    
        std::swap(vec[i], vec[minIndex]);
    }
    
    return;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    
    sortingByChoice(vec);

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';

    return 0;
}