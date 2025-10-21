#include <iostream>
#include <vector>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

std::ostream & operator<<(std::ostream & os, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        if (i > 0) os << ' ';
        os << rhs[i];
    }
    os << '\n';
    return os;
}

std::vector<int> merge(const std::vector<int> & lhs, const std::vector<int> & rhs) {
    std::vector<int> answer;
    size_t lhsIndex = 0, rhsIndex = 0;
    while (lhsIndex < lhs.size() && rhsIndex < rhs.size()) {
        if (lhs[lhsIndex] <= rhs[rhsIndex]) {
            answer.push_back(lhs[lhsIndex]);
            ++lhsIndex;
        } else {
            answer.push_back(rhs[rhsIndex]);
            ++rhsIndex;
        }
    }

    for (; lhsIndex < lhs.size(); ++lhsIndex) {
        answer.push_back(lhs[lhsIndex]);
    }

    for (; rhsIndex < rhs.size(); ++rhsIndex) {
        answer.push_back(rhs[rhsIndex]);
    }

    return answer;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> answer(m);
    std::cin >> answer;

    for (int i = 1; i < n; ++i) {
        std::cin >> m;
        std::vector<int> temp(m);
        std::cin >> temp;
        answer = merge(answer, temp);
    }

    std::cout << answer;
    return 0;
}