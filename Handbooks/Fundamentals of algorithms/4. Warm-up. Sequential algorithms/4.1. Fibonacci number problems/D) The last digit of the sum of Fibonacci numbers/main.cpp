#include <iostream>
#include <vector>

typedef std::vector<std::vector<long long>> matrix;
typedef std::vector<long long> row;

std::ostream & operator<<(std::ostream & os, const matrix & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) std::cout << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

matrix product(const matrix & lhs, const matrix & rhs) {
    if (lhs[0].size() != rhs.size()) {
        throw std::logic_error("Wrong dimensions");
    }

    int n = lhs.size(), m = rhs[0].size();
    matrix answer(n, row(m, 0));

    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t k = 0; k < rhs[0].size(); ++k) {
            for (size_t j = 0; j < lhs[0].size(); ++j) {
                answer[i][k] = (answer[i][k] + lhs[i][j] * rhs[j][k]) % 10;
            }        
        }
    }

    return answer;
}

matrix fastPow(const matrix & lhs, long long n) {
    if (n < 0) {
        throw std::logic_error("Realization don't have minus degree logic");
    }

    matrix answer(lhs.size(), row(lhs[0].size(), 0));
    for (size_t i = 0; i < lhs.size(); ++i) {
        answer[i][i] = 1;
    }

    for (int i = 62; i >= 0; --i) {
        answer = product(answer, answer);
        if (n & (1ll << i)) {
            answer = product(answer, lhs);
        }
    }

    return answer;
}

int main() {
    matrix F = {
        {0, 1},
        {1, 1}
    };

    long long n;
    std::cin >> n;
    F = fastPow(F, n + 2);
    
    // std::cout << F;
    
    std::cout << ((F[0][1] - 1) + 10) % 10 << '\n';
    return 0;
}