#include <iostream>
#include <unordered_map>
#include <climits>
#include <cmath>

std::unordered_map<int, long long> memo4;

long long moves3(int n) {
    if (n <= 0) return 0;
    return (1LL << n) - 1;
}

long long moves4(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    if (memo4.contains(n)) {
        return memo4[n];
    }

    long long best = LLONG_MAX;
    for (int k = 1; k < n; ++k) {
        long long candidate = 2 * moves4(k) + moves3(n - k);
        if (candidate < best) {
            best = candidate;
        }
    }

    memo4[n] = best;
    return best;
}

int main() {
    int n;
    std::cin >> n;
    std::cout << moves4(n) << '\n';
    return 0;
}