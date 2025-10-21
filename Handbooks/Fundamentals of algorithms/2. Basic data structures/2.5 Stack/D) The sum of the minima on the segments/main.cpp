#include <iostream>
#include <deque>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::deque<int> window;
    long long answer = 0;
    for (int i = 0; i <= n; ++i) {
        if (i >= k) {
            answer += a[window.front()];
        }

        // std::cout << "i = " << i 
        //           << " window.back(): " << (window.empty() ? -1 : a[window.front()])
        //           << " answer = " << answer << '\n';

        if (i == n) {
            continue;
        }

        while (!window.empty() && window.front() <= i - k) {
            window.pop_front();
        }

        while (!window.empty() && a[window.back()] >= a[i]) {
            window.pop_back();
        }

        window.push_back(i);
    }
    std::cout << answer << '\n';

    return 0;
}