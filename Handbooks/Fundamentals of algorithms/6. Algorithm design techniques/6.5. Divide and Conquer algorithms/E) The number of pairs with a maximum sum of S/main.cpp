#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    long long n, S;
    std::cin >> n >> S;
    std::vector<long long> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        int endIndex = std::upper_bound(vec.begin() + i + 1, vec.end(), S - vec[i]) - vec.begin() - 1;
        if (endIndex == i) {
            break;
        }
        answer += endIndex - i;
    }

    std::cout << answer << '\n';
    
    return 0;
}