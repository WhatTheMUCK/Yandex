#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>


template <typename T>
std::ostream & operator<<(std::ostream & os, const std::vector<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (i > 0) os << ' ';
        os << rhs[i];
    }
    os << '\n';
    return os;
}

long long calculate(long long lhs, char op, long long rhs) {
    if (op == '+') {
        return lhs + rhs;
    }

    if (op == '-') {
        return lhs - rhs;
    }

    // Будем считать что оставшаяся операция - умножение
    return lhs * rhs;
    
}

int main() {
    std::string input;
    std::cin >> input;
    int n = static_cast<int>(input.size());
    n /= 2;
    std::vector<int> d(n + 1);
    std::vector<char> op(n);
    for (int i = 0; i < n; ++i) {
        d[i] = input[2 * i] - '0';
        op[i] = input[2 * i + 1];
    }
    d.back() = input.back() - '0';

    std::vector<std::vector<long long>> mins(n + 1, std::vector<long long>(n + 1, std::numeric_limits<long long>::max()));
    std::vector<std::vector<long long>> maxs(n + 1, std::vector<long long>(n + 1, std::numeric_limits<long long>::min()));

    for (int i = 0; i <= n; ++i) {
        mins[i][i] = d[i];
        maxs[i][i] = d[i];
    }

    for (int s = 1; s <= n; ++s) {
        for (int l = 0; l <= n - s; ++l) {
            int r = l + s;
            for (int m = l; m < r; ++m) {
                long long a = calculate(mins[l][m], op[m], mins[m + 1][r]);
                long long b = calculate(mins[l][m], op[m], maxs[m + 1][r]);
                long long c = calculate(maxs[l][m], op[m], mins[m + 1][r]);
                long long d = calculate(maxs[l][m], op[m], maxs[m + 1][r]);
                mins[l][r] = std::min({mins[l][r], a, b, c, d});
                maxs[l][r] = std::max({maxs[l][r], a, b, c, d});
            }
        }
    }

    std::cout << maxs[0][n] << '\n';

    return 0;
}