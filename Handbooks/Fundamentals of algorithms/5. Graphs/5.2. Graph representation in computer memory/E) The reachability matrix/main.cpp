#include <iostream>
#include <vector>

template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}


template <typename T>
matrix<T> customProduct(const matrix<T> & lhs, const matrix<T> & rhs, matrix<T> & main){
    matrix<T> answer(lhs.size(), row<T>(lhs[0].size(), 0));
    for (size_t i = 0; i < lhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j) {
            for (size_t k = 0; k < lhs[0].size(); ++k) {
                answer[i][j] += lhs[i][k] * rhs[k][j];
            }
            answer[i][j] = std::min(answer[i][j], 1);
            main[i][j] = std::max(main[i][j], answer[i][j]);
        }
    }
    return answer;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n;
    std::cin >> n;
    matrix<int> startGraph(n, row<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> startGraph[i][j];
        }
    }
    matrix<int> helper = startGraph, answer = startGraph;
    for (int i = 1; i < n; ++i) {
        helper = customProduct(helper, startGraph, answer);
    }

    std::cout << answer;

    return 0;   
}

