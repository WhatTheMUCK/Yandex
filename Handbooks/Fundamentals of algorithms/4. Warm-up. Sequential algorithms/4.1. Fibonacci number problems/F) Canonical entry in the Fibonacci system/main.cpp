#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<long long> canonical = {1, 1};
    while (n > canonical.back()) {
        int m = static_cast<int>(canonical.size());
        canonical.push_back(canonical[m - 1] + canonical[m - 2]);
    }

    if (canonical.back() > n) {
        canonical.pop_back();
    }

    int m = static_cast<int>(canonical.size());
    for (int i = m - 1; i > 0; --i) {
        if (n >= canonical[i]) {
            std::cout << '1';
            n -= canonical[i];
        } else {
            std::cout << '0';
        }
    }
    std::cout << '\n';

    return 0;
}