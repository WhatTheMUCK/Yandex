#include <iostream>
#include <unordered_set>

std::unordered_set<long long> visited;

void generate(long long number, int diff, int curLen, int n) {
    if (visited.contains(number)) {
        return;
    }

    visited.insert(number);

    if (curLen == n) {
        std::cout << number << '\n';
        return;
    }

    int lastDigit = number % 10;
    if (lastDigit + diff <= 9) {
        generate(10 * number + (lastDigit + diff), diff, curLen + 1, n);
    }

    if (lastDigit - diff >= 0) {
        generate(10 * number + (lastDigit - diff), diff, curLen + 1, n);
    }
    return;
}

int main() {
    long long n, k;
    std::cin >> n >> k;

    for (int i = 1; i < 10; ++i) {
        generate(i, k, 1, n);
    }
    return 0;
}