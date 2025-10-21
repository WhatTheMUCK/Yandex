#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


bool enough(const std::vector<int> & x, int k, int curLength) {
    int curEnd = x.front() - 1;
    for (size_t i = 0; i < x.size(); ++i) {
        if (x[i] <= curEnd) {
            continue;
        }

        curEnd = x[i] + curLength;
        --k;
    }

    return (k >= 0);
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }
    if (k >= n) {
        std::cout << "0\n";
        return 0;
    }

    std::sort(x.begin(), x.end());

    int l = 0, r = x.back() - x.front();
    while (l < r) {
        int m = (l + r) / 2;
        if (enough(x, k, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    std::cout << l << '\n';

    return 0;
}