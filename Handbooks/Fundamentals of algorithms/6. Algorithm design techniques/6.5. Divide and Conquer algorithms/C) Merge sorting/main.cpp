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

void merge(int start1, int end1, int start2, int end2, std::vector<int> & vec) {
    std::vector<int> answer;
    int lhsIndex = start1, rhsIndex = start2;
    while (lhsIndex <= end1 && rhsIndex <= end2) {
        if (vec[lhsIndex] <= vec[rhsIndex]) {
            answer.push_back(vec[lhsIndex]);
            ++lhsIndex;
        } else {
            answer.push_back(vec[rhsIndex]);
            ++rhsIndex;
        }
    }

    for (; lhsIndex <= end1; ++lhsIndex) {
        answer.push_back(vec[lhsIndex]);
    }

    for (; rhsIndex <= end2; ++rhsIndex) {
        answer.push_back(vec[rhsIndex]);
    }

    for (int i = 0; i <= end2 - start1; ++i) {
        vec[start1 + i] = answer[i];
    }
    return;
}

void mergeSort(std::vector<int> & vec, int l, int r) {
    if (l == r) {
        return;
    }

    int middle = (l + r) / 2;
    mergeSort(vec, l, middle);
    mergeSort(vec, middle + 1, r);
    merge(l, middle, middle + 1, r, vec);
    return;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> answer(n);
    std::cin >> answer;

    mergeSort(answer, 0, n - 1);

    std::cout << answer;
    return 0;
}