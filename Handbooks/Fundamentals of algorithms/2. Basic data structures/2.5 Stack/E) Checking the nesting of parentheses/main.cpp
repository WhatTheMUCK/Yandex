#include <iostream>
#include <stack>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::unordered_map<char, char> mp = {
        {')', '('},
        {']', '['},
        {'}', '{'}
    };

    std::stack<char> st;
    char curChar;

    while (std::cin >> curChar) {
        if (st.empty()) {
            st.push(curChar);
            continue;
        }

        if (mp.contains(curChar)) {
            if (st.top() == mp[curChar]) {
                st.pop();
                continue;
            } else {
                break;
            }
        } else {
            st.push(curChar);
        }
    }

    std::cout << (st.empty() ? "YES" : "NO") << '\n';

    return 0;
}