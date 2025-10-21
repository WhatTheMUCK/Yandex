#include <iostream>
#include <vector>


int main() {
    int n;
    std::cin >> n;
    std::vector<int> answer;
    int k = 1;
    while (n >= k) {
        answer.push_back(k);
        n -= k;
        ++k;
    }

    answer.back() += n;
    n = 0;

    std::cout << answer.size() << '\n';

    return 0;
}