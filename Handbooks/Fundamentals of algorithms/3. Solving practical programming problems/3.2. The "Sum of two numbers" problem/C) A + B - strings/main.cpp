#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::string A, B;
    std::cin >> A >> B;
    for (int i = 0; i < n; ++i) {
        std::cout << A[i] << B[i];
    }
    std::cout << '\n';
    return 0;
}