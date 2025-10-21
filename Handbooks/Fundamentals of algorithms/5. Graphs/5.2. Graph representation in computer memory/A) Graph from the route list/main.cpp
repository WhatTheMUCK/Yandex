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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    matrix<int> graph1(n, row<int>(n, 0)), graph2(n, row<int>(n, 0));
    for (int i = 0; i < m; ++i) {
        int k;
        std::cin >> k;
        std::vector<int> route(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> route[j];
            if (j > 0) {
                int prev = route[j - 1] - 1;
                int cur = route[j] -1;
                graph1[cur][prev] = 1;
                graph1[prev][cur] = 1;
            }
        }

        for (int j1 = 0; j1 < k; ++j1) {
            for (int j2 = j1 + 1; j2 < k; ++j2) {
                int prev = route[j1] - 1;
                int cur = route[j2] - 1;
                graph2[cur][prev] = 1;
                graph2[prev][cur] = 1;
            }
        }
    }

    std::cout << graph1 << graph2;
    return 0;
}

