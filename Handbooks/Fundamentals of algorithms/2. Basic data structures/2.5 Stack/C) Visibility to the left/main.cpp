#include <iostream>
#include <vector>
#include <stack>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::stack<int> st;
    std::vector<int> ans(n);

    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.top()] < a[i]) {
            st.pop();
        }

        int prevGe = st.empty() ? -1 : st.top();
        ans[i] = i - prevGe - 1;

        st.push(i);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << (i == n-1 ? '\n' : ' ');
    }

    return 0;
}