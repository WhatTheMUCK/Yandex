#include <iostream>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::stack<int> st;
    for (int i = 0 ; i < n; ++i) {
        int mode;
        std::cin >> mode;

        if (mode == 1) {
            int x;
            std::cin >> x;
            st.push(x);
        } else if (mode == 2) {
            if (!st.empty()) {
                st.pop();
            }
        }

        std::cout << (st.empty() ? -1 : st.top()) << '\n';
    }

    return 0;
}