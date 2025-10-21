#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int f1 = 1, f2 = 1;
    while (f2 < n) {
        int tmp = f1;

        if (f2 + tmp > n) {
            break;
        }
        
        f1 = f2;
        f2 = f1 + tmp;
    }
    std::cout << f1 << ' ' << f2 << '\n';
    return 0;
}