#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::deque<int> dq;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int mode;
        std::cin >> mode;
        
        if (mode == 1) {
            int x;
            std::cin >> x;
            dq.push_back(x);
        }

        if (mode == 2) {
            dq.pop_front();
        }

        std::cout << (dq.empty() ? -1 : dq.front()) << '\n';
    }

    return 0;
}