#include <iostream>
#include <vector>
#include <fstream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int money;
    std::cin >> money;

    std::vector<std::vector<int>> solutions;

    for (int cnt10 = 0; cnt10 <= money / 10; ++cnt10) {
        int remaining_after_10 = money - cnt10 * 10;
        for (int cnt5 = 0; cnt5 <= remaining_after_10 / 5; ++cnt5) {
            int remaining = remaining_after_10 - cnt5 * 5;
            int cnt1 = remaining;

            std::vector<int> set;
            set.push_back(cnt1 + cnt5 + cnt10);

            for (int i = 0; i < cnt10; ++i) set.push_back(10);
            for (int i = 0; i < cnt5; ++i) set.push_back(5);
            for (int i = 0; i < cnt1; ++i) set.push_back(1);

            solutions.push_back(set);
        }
    }

    std::cout << solutions.size() << '\n';
    for (const auto& sol : solutions) {
        for (size_t i = 0; i < sol.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << sol[i];
        }
        std::cout << '\n';
    }

    return 0;
}