#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, L;
    std::cin >> n >> L;
    std::vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }
    std::sort(x.begin(), x.end());
    int answer = 1;
    long long lastEnd = x[0] + L;
    for (int i = 1; i < n; ++i) {
        if (x[i] <= lastEnd) {
            continue;
        }

        ++answer;
        lastEnd = x[i] + L;
    }

    std::cout << answer << '\n';
    
    return 0;
}