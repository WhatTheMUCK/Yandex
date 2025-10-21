#include <iostream>
#include <unordered_set>


int main() {
    int q;
    std::cin >> q;
    std::unordered_set<int> st;
    for (int i = 0 ; i < q; ++i) {
        int mode, x;
        std::cin >> mode >> x;
        if (mode == 1) {
            st.insert(x);
            continue;
        }

        std::cout << st.contains(x) << '\n';
    }
    return 0;
}