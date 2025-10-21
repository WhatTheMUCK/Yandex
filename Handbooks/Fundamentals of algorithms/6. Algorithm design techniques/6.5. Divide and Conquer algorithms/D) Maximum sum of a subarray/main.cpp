#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>


std::istream & operator>>(std::istream & is, std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        is >> vec[i];
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, std::vector<int> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i > 0) os << ' ';
        os << vec[i];
    }
    return os;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    std::cin >> vec;
    long long maxSum = std::numeric_limits<int>::min(), minSum = 0, curSum = 0;
    for (int value : vec) {
        curSum += value;
        maxSum = std::max({maxSum, curSum, curSum - minSum});
        minSum = std::min(minSum, curSum);
    }

    std::cout << maxSum << '\n';
    return 0;
}