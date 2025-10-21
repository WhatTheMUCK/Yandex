#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

int main() {
    int n, m;
    std::cin >> n >> m;
    matrix<bool> field(n + 1, row<bool>(m + 1, false));
    for (int i = 1 ; i <= n; ++i) {
        field[i][0] = !field[i - 1][0];
    }

    for (int i = 1; i <= m; ++i) {
        field[0][i] = !field[0][i - 1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            field[i][j] = !std::min({field[i - 1][j], field[i -1][j - 1], field[i][j - 1]});
        }
    }

    std::cout << (field[n][m] ? "Win" : "Lose") << '\n';
    return 0;
}