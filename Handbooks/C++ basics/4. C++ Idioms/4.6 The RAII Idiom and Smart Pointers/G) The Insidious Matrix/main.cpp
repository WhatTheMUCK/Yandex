#include "matrix.h"
#include <iostream>

int main() {
    size_t m, n;
    std::cin >> m >> n;
    Matrix<int> A(m, n);
    // ...
    A = FillMatrix<int>(m, n);
    // std::cout << A.GetRows() << ' ' << A.GetColumns() << '\n';
    // A[m - 1][n - 1] = 1;
    std::cout << A << "\n";
    return 0;
}