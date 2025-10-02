#include <iostream>
#include <vector>
#include <deque>

std::ostream & operator<<(std::ostream & os, const std::pair<int, int> & rhs) {
    return os << '(' << rhs.first << ' ' << rhs.second << ')';
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    std::deque<std::pair<int, int>> window;
    for (int i = 0; i < n; ++i) {
        while (!window.empty() && window.front().second <= i - k) {
            window.pop_front();
        }

        while (!window.empty() && vec[i] <= window.back().first) {
            window.pop_back();
        }

        window.push_back({vec[i], i});

        if (i >= k - 1) {
            std::cout << window.front().first << '\n';
        }
    }

    return 0;
}