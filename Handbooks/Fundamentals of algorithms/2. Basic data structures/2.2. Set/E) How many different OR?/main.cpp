#include <iostream>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<int> answer;
    std::unordered_set<int> st;
    for (int i = 0; i < n; ++i) {
        int tmp;
        std::cin >> tmp;
        std::unordered_set<int> cur;
        for (int value : st) {
            int curOR = value | tmp;
            cur.insert(curOR);
            answer.insert(curOR);
        }
        cur.insert(tmp);
        answer.insert(tmp);
        st = cur;
    }

    std::cout << answer.size() << '\n';

    return 0;
}