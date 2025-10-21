#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n;
    std::cin >> n;
    std::vector<long long> vec(n);
    for (int i = 0 ; i < n; ++i) {
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end());
    std::vector<long long> helper = {vec[n - 1] * vec[n - 2], vec[n - 3] * vec[n - 4], vec[0] * vec[1], vec[2] * vec[3]};
    std::cout << std::max({helper[0] * helper[1], helper[0] * helper[2], helper[2] * helper[3]}) << '\n';
    return 0;
}