#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, S;
    std::cin >> n >> S;
    std::vector<int> souvenirs(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> souvenirs[i];
    }
    std::sort(souvenirs.begin(), souvenirs.end());
    int answer = 0;
    for (size_t i = 0; i < souvenirs.size() && S >= souvenirs[i]; ++i) {
        ++answer;
        S -= souvenirs[i];
    }

    std::cout << answer << '\n';

    return 0;
}