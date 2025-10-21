#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    std::cin >> vec[0];
    for (int i = 1; i < n; ++i) {
        std::cin >> vec[i];
        vec[i] = std::min(vec[i - 1], vec[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';
    
    return 0;
}