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

    int d, n = 0;
    std::cin >> d;
    matrix<int> graph(100, row<int>(100, 0));
    for (int i = 0; i < d; ++i) {
        int k;
        std::cin >> k;
        int chief;
        std::cin >> chief;
        n = std::max(n, chief);
        for (int j = 1; j < k; ++j) {
            int worker;
            std::cin >> worker;
            n = std::max(n, worker);
            graph[chief - 1][worker - 1] = 1;
            graph[worker - 1][chief - 1] = -1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) std::cout << ' ';
            std::cout << graph[i][j];
        }
        std::cout << '\n';
    }

    return 0;   
}

