#include <iostream>
#include <vector>


int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    std::vector<int> answer;
    for (int i = 0; i < n; ++i) {
        if (i == 0 || i == n - 1) {
            answer.push_back(vec[i]);
            continue;
        }

        if (vec[i - 1] > vec[i] && vec[i] < vec[i + 1]) {
            continue;
        }
        answer.push_back(vec[i]);
    }

    int k = static_cast<int>(answer.size());
    std::cout << k << '\n';
    for (int i = 0; i < k; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << answer[i];
    }
    std::cout << '\n';

    return 0;
}