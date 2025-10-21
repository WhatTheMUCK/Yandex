#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int candidate = -1;
    int count = 0;
    for (int x : a) {
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            ++count;
        } else {
            --count;
        }
    }
    int freq = 0;
    for (int x : a) {
        if (x == candidate) ++freq;
    }

    std::cout << (freq > n / 2 ? 1 : 0) << '\n';
    return 0;
}