#include <iostream>
#include <vector>
#include <algorithm>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> firstSubsequence(n);
    std::cin >> firstSubsequence;

    std::cin >> m;
    std::vector<int> secondSubsequence(m);
    std::cin >> secondSubsequence;
    std::vector<std::vector<int>> LCS(n + 1, std::vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int deletionFirst = LCS[i - 1][j];
            int deletionSecond = LCS[i][j - 1];
            int match = LCS[i - 1][j - 1] + 1;
            LCS[i][j] = std::max(deletionFirst, deletionSecond);
            if (firstSubsequence[i - 1] == secondSubsequence[j - 1]) {
                LCS[i][j] = std::max(LCS[i][j], match);
            }
        }
    }

    std::cout << LCS[n][m] << '\n';
    return 0; 
}