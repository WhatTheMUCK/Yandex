#include <iostream>
#include <vector>

std::vector<std::vector<int>> Transpose(const std::vector<std::vector<int>> & matrix) {
    size_t row = matrix.size(), col = matrix[0].size(); // Гарантируется, что вектор matrix непуст и все его элементы имеют равную ненулевую длину.
    std::vector<std::vector<int>> answer(col, std::vector<int>(row));
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            answer[j][i] = matrix[i][j];
        }
    }
    return answer;
}

int main() {
    int row, col;
    std::cin >> row >> col;
    std::vector<std::vector<int>> matrix(row, std::vector<int>(col));
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    std::vector<std::vector<int>> matrixT = Transpose(matrix);
    for (size_t i = 0; i < col; ++i) {
        for (size_t j = 0; j < row; ++j) {
            std::cout << matrixT[i][j] << ' ';
        }
        std::cout << '\n';
    }
    return 0;
}