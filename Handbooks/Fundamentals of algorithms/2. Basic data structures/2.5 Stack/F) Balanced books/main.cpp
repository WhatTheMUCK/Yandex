#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    int answer = 0;
    std::stack<long long> st;
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < n; ++i) {
        long long book;
        std::cin >> book;
        book = ((book  % 2) + 2) % 2;
        if (st.empty()) {
            if (book == 0) {
                continue;
            }

            st.push(i);
            continue;
        }

        if (book == 0) {
            int left = st.top();
            st.pop();
            pairs.push_back({left, i});

        } else {
            st.push(i);
        }
    }
    std::sort(pairs.begin(), pairs.end());
    std::vector<std::pair<int, int>> pairsEdited;
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (i == 0) {
            pairsEdited.push_back(pairs[i]);
            continue;
        } 

        auto [left1, right1] = pairsEdited.back();
        auto [left2, right2] = pairs[i];
        if (left2 < right1 || right1 + 1 == left2) {
            int left = std::min(left1, left2);
            int right = std::max(right1, right2);
            pairsEdited.back() = {left, right};
        } else {
            pairsEdited.push_back(pairs[i]);
        }
    }

    for (const auto & [l, r] : pairsEdited) {
        answer = std::max(answer, r - l + 1);
    }

    std::cout << answer << '\n';
    return 0;
}