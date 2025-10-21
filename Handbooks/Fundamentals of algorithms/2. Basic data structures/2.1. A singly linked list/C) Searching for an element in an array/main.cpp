#include <iostream>
#include <vector>
#include <algorithm>


int lowerBound(int target, const std::vector<std::pair<int, int>> & vec) {
    int n = static_cast<int>(vec.size());
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (vec[m].first >= target) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
}

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<int, int>> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i].first;
        vec[i].second = i;
    }
    std::sort(vec.begin(), vec.end());

    int target;
    for (int i = 0; i < q; ++i) {
        std::cin >> target;
        int targetIndex = lowerBound(target, vec);
        if (targetIndex == n || vec[targetIndex].first != target) {
            std::cout << -1 << '\n';
            continue;
        }
        std::cout << vec[targetIndex].second + 1<< '\n';
    }
    return 0;
}