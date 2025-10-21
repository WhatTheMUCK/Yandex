#include <iostream>
#include <queue>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        pq.push(a);
    }

    long long answer = 0;
    for (int i = 0; i < k && pq.top() > 0; ++i) {
        answer += pq.top();
        pq.pop();
    }

    std::cout << answer << '\n';

    return 0;
}