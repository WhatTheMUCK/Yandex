#include <iostream>
#include <queue>

int main() {
    int n;
    size_t k;
    std::cin >> n >> k;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        while (!pq.empty() && pq.top() <= a) {
            pq.pop();
        }

        if (pq.size() == k) {
            continue;
        }

        ++answer;
        pq.push(b);
    }

    std::cout << answer << '\n';
    return 0;
}