#include <iostream>
#include <utility>
#include <vector>

std::pair<size_t, size_t> MatrixArgMax(const std::vector<std::vector<int>> & matrix) {
    std::pair<size_t, size_t> answer = {0, 0};
    int maxNumber = matrix[0][0];
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j) {
            if (maxNumber < matrix[i][j]) {
                answer = {i, j};
                maxNumber = matrix[i][j];
            }
        }
    }
    return answer;
}

std::ostream & operator<<(std::ostream & os, const std::pair<size_t, size_t> pair) {
    return os << pair.first << ' ' << pair.second;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(k));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < k; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    std::cout << MatrixArgMax(matrix) << '\n';
    return 0;
}