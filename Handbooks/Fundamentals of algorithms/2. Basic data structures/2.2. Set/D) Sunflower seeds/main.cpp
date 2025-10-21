#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> st;
    std::vector<std::unordered_map<int, int>> p(n);
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int temp;
            std::cin >> temp;
            if (p[i].contains(temp)) {
                continue;
            }
            ++st[temp];
            ++p[i][temp];
        }
    }
    std::vector<int> c;
    bool canBe = true;
    for (const std::pair<const int, int> & elem : st) {
        if (elem.second == n) {
            c.push_back(elem.first);
            continue;
        }

        if (elem.second != 1) {
            canBe = false;
            break;
        }
    }

    if (!canBe) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n" << c.size() << '\n';
    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        for (int value : c) {
            p[i].erase(value);
        }
        std::cout << p[i].size();
    }
    std::cout << '\n';
    return 0;
}