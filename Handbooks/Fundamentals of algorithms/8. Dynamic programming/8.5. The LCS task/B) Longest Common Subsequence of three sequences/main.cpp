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
    int n, m, l;
    std::cin >> n;
    std::vector<int> firstSubsequence(n);
    std::cin >> firstSubsequence;

    std::cin >> m;
    std::vector<int> secondSubsequence(m);
    std::cin >> secondSubsequence;

    std::cin >> l;
    std::vector<int> thirdSubsequence(l);
    std::cin >> thirdSubsequence;

    std::vector<std::vector<std::vector<int>>> LCS(n + 1, std::vector<std::vector<int>>(m + 1, std::vector<int>(l + 1, 0)));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int k = 1; k <= l; ++k) {
                int deletionFirst = LCS[i - 1][j][k];
                int deletionSecond = LCS[i][j - 1][k];
                int deletionThird = LCS[i][j][k - 1];
                int match = LCS[i - 1][j - 1][k - 1] + 1;
                LCS[i][j][k] = std::max({deletionFirst, deletionSecond, deletionThird});
                if (firstSubsequence[i - 1] == secondSubsequence[j - 1] && secondSubsequence[j - 1] == thirdSubsequence[k - 1]) {
                    LCS[i][j][k] = std::max(LCS[i][j][k], match);
                }
            }
        }
    }

    std::cout << LCS[n][m][l] << '\n';
    return 0; 
}