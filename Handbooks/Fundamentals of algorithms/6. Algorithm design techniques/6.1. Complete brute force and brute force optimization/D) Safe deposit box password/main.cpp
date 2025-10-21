#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> digits(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> digits[i];
    }

    std::sort(digits.begin(), digits.end());
    do {
        long long number = 0;
        for (int digit : digits) {
            number = number * 10 + digit;
        }
        if (number % m == 0) {
            std::string answer = std::string(digits.begin(), digits.end());
            for (size_t i = 0; i < answer.size(); ++i) {
                answer[i] += '0';
            }
            std::cout << answer << '\n';
            return 0;
        }
    } while (std::next_permutation(digits.begin(), digits.end()));

    std::cout << "No solutions\n";
    return 0;
}