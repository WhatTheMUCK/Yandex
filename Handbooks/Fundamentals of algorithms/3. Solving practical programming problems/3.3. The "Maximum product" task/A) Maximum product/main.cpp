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
    std::cout << vec[n - 1] * vec[n - 2] << '\n';
    return 0;
}