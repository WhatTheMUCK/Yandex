#include <iostream>
#include <vector>
#include <stack>
#include <queue>


template <typename T>
using row = std::vector<T>;

template <typename T>
using matrix = std::vector<row<T>>;

template <typename T>
std::istream & operator>>(std::istream & is, matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j){
            is >> rhs[i][j];
        }
    }
    return is;
}

template <typename T>
std::ostream & operator<<(std::ostream & os, const matrix<T> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        for (size_t j = 0; j < rhs[0].size(); ++j){
            if (j > 0) os << ' ';
            os << rhs[i][j];
        }
        os << '\n';
    }
    return os;
}

template <typename T, typename V>
std::ostream & operator<<(std::ostream & os, const std::pair<T, V> rhs) {
    return os << '{' << rhs.first << ", " << rhs.second << "} ";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int t;
    std::cin >> t;

    for (int test = 0; test < t; ++test) {
        int n, m, k, s;
        std::cin >> n >> m >> k >> s;

        matrix<char> window(n + 1, row<char>(m + 1, '.'));
        std::vector<matrix<int>> helper(k, matrix<int>(n + 1, row<int>(m + 1, 0)));

        std::vector<int> amount(k);
        std::vector<std::vector<std::pair<int, int>>> possibleAngle(k);
        
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char symbol;
                std::cin >> symbol;
                
                window[i][j] = symbol;
                if (symbol == '.') {
                    continue;
                }

                ++amount[symbol - '1'];
            }
        }

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                char symbol = window[i][j];
                if (symbol == '.') {
                    continue;
                }

                ++helper[symbol - '1'][i][j];

                if (i == 0 && j == 0) {
                    continue;
                }
                for (int index = 0; index < k; ++index) {
                    if (i == 0) {
                        helper[index][i][j] += helper[index][i][j - 1];
                        continue;
                    }

                    if (j == 0) {
                        helper[index][i][j] += helper[index][i - 1][j];
                        continue;
                    }

                    helper[index][i][j] += helper[index][i][j - 1] + helper[index][i - 1][j] - helper[index][i - 1][j - 1];

                    if (i >= s && j >= s) {
                        int amountInArea = helper[index][i][j] - (helper[index][i - s][j] + helper[index][i][j - s] - helper[index][i - s][j - s]);
                        if (amountInArea == amount[index])
                        possibleAngle[index].push_back({i + 1 - s, j + 1 - s});
                    }
                }
            }
        }

        std::stack<int> DFS;
        int startMask = 0;
        matrix<char> startWindow(n + 1, row<char>(m + 1, '.'));
        DFS.push(startMask);
        long long answer = 0;
        while (!DFS.empty()) {
            auto mask = DFS.top();
            DFS.pop();
            for (int i = 0; i < k; ++i) {
                int curMask = mask;
                if ((curMask & (1 << i)) != 0) {
                    continue;
                }
                curMask |= (1 << i);
                for (size_t j = 0; j < possibleAngle[i].size(); ++j) {
                    auto [leftUpI, leftUpj] = possibleAngle[i][j];
                    bool canBeAnswer = true; 
                    for (int offsetI = 0; offsetI < s && canBeAnswer; ++offsetI) {
                        for (int offsetJ = 0; offsetJ < s && canBeAnswer; ++offsetJ) {
                            int curI = leftUpI + offsetI, curJ = leftUpj + offsetJ;
                            if (!(0 < curI && curI <= n) || !(0 < curJ && curJ <= m)) {
                                continue;
                            }

                            if (window[curI][curJ] != i + '1') {
                                if (window[curI][curJ] == '.') {
                                    canBeAnswer = false;
                                    continue;
                                }

                                if ((curMask & (1 << (window[curI][curJ] - '1'))) != 0) {
                                    canBeAnswer = false;
                                    continue;
                                }
                            }
                        }
                    }

                    if (!canBeAnswer) {
                        continue;
                    }

                    if (curMask == ((1 << k) - 1)) {
                        ++answer;
                        continue;
                    }

                    DFS.push(curMask);
                }
            }
        }

        std::cout << answer << '\n';
    }

    return 0;
}