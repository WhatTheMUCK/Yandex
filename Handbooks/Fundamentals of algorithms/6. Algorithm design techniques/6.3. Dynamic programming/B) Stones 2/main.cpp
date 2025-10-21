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
    for (int i = 1; i <= m; ++i) {
        field[0][i] = !std::min(field[0][i - 1], field[0][std::max(i - 2, 0)]);
    }

    for (int i = 1; i <= n; ++i) {
        field[i][0] = !std::min(field[i - 1][0], field[std::max(i - 2, 0)][0]);
    }

    for (int i = 1; i <= m; ++i) {
        field[1][i] = !std::min({field[0][i], field[1][i - 1], field[1][std::max(i - 2, 0)]});
    }
    
    for (int i = 1; i <= n; ++i) {
        field[i][1] = !std::min({field[i][0], field[i - 1][1], field[std::max(i - 2, 0)][1]});
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 2; j <= m; ++j) {
            field[i][j] = !std::min({
                field[i - 1][j], field[i][j - 1],
                field[i - 2][j], field[i][j - 2],
                field[i - 2][j - 1], field[i - 1][j - 2]
            });
        }
    }

    std::cout << (field[n][m] ? "Win" : "Lose") << '\n';
    return 0;
}