#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>


int myFront(std::deque<int> & dq) {
    if (dq.empty()) {
        return 0;
    }

    int answer = dq.front();
    dq.pop_front();
    return answer;
}

int main() {
    std::deque<int> A, B;
    int n, m;
    std::cin >> n;
    for (int i = 0; i <= n; ++i) {
        int a;
        std::cin >> a;
        A.push_front(a);
    }

    std::cin >> m;
    for (int i = 0; i <= m; ++i) {
        int b;
        std::cin >> b;
        B.push_front(b);
    }

    std::vector<int> answer;
    while (!A.empty() || !B.empty()) {
        int cur = myFront(A) + myFront(B);
        answer.push_back(cur);
    }
    std::reverse(answer.begin(), answer.end());

    std::cout << answer.size() - 1 << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}