#include <iostream>
#include <unordered_map>

std::unordered_map<int, long long> memoization;

long long fibonachi(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    if (memoization.contains(n)) {
        return memoization[n];
    }

    memoization[n] = fibonachi(n - 1) + fibonachi(n - 2);
    return memoization[n];
}

int main() {
    int n;
    std::cin >> n;
    std::cout << fibonachi(n) << '\n';
    return 0;
}