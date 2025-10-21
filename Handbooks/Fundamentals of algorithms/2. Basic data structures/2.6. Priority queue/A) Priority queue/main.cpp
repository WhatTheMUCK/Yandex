#include <iostream>
#include <queue>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        int mode;
        std::cin >> mode;
        if (mode == 1) {
            int x;
            std::cin >> x;
            pq.push(x);
        } else if (mode == 2) {
            if (!pq.empty()) {
                pq.pop();
            }
        }

        std::cout << (pq.empty() ? -1 : pq.top()) << '\n';
    }
    return 0;
}