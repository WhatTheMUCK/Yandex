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

    int g, n = 1;
    matrix<int> graph(100, row<int>(100, 0));
    std::cin >> g;
    for (int i = 0; i < g; ++i) {
        int k;
        std::cin >> k;
        std::vector<int> friends(k);
        for (int j = 0; j < k; ++j) {
            std::cin >> friends[j];
            n = std::max(n, friends[j]);
        }

        for (int j1 = 0; j1 < k; ++j1) {
            for (int j2 = j1 + 1; j2 < k; ++j2) {
                int prev = friends[j1] - 1, cur = friends[j2] - 1;
                graph[cur][prev] = 1;
                graph[prev][cur] = 1;
            }
        }
    }

    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) std::cout << ' ';
            std::cout << graph[i][j];
        }
        std::cout << '\n';
    }
    
    return 0;
}

