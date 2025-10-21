#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> k(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> k[i];
    }
    int q;
    std::cin >> q;
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (k[m] == q) {
            std::cout << m << '\n';
            return 0;
        }

        if (k[m] < q) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (k[l] != q) {
        std::cout << "-1\n";
    } else {
        std::cout << l << '\n';
    }
    return 0;
}