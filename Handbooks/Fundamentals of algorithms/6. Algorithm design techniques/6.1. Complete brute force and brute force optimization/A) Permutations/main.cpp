#include <iostream>

long long permutations(int n) {
    if (n == 1 || n == 0) {
        return 1;
    }

    return n * permutations(n - 1);
}

int main() {
    int n;
    std::cin >> n;
    std::cout << permutations(n) << '\n';
    return 0;
}