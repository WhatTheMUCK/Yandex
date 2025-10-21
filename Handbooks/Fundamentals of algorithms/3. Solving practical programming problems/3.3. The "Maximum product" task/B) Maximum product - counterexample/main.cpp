#include <iostream>

int main() {
    int n;
    std::cin >> n;
    if (n < 7) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    std::cout << n;
    for (int i = 1; i < n; ++i) {
        std::cout << ' ' << i;
    }
    std::cout << '\n';
    
    return 0;
}