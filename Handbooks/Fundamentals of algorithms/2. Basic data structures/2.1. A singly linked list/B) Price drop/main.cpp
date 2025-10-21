#include <iostream>
#include <vector>
#include <algorithm>

std::ostream & operator<<(std::ostream & os, std::pair<int, int> rhs) {
    return os << rhs.first << ' ' << rhs.second;
}
int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    int minLeft = vec[0], maxLeft = vec[0];
    int minLeftInd = 0, maxLeftInd = 0;
    int minDiff = vec[0] - vec[1], maxDiff = vec[0] - vec[1];
    std::pair<int, int> minDiffIndices = {0, 1}, maxDiffIndices = {0, 1};
    for (int i = 1; i < n; ++i) {
        int potentialMinDiff = minLeft - vec[i];
        int potentialMaxDiff = maxLeft - vec[i];
        if (minDiff > potentialMinDiff) {
            minDiffIndices = {minLeftInd, i};
            minDiff = potentialMinDiff;
        } 

        if (maxDiff < potentialMaxDiff) {
            maxDiffIndices = {maxLeftInd, i};
            maxDiff = potentialMaxDiff;
        }

        if (minLeft > vec[i]) {
            minLeftInd = i;
            minLeft = vec[i];
        }

        if (maxLeft < vec[i]) {
            maxLeftInd = i;
            maxLeft = vec[i];
        }
    }
    
    ++minDiffIndices.first;
    ++minDiffIndices.second;
    ++maxDiffIndices.first;
    ++maxDiffIndices.second;

    std::cout << minDiffIndices << '\n' << maxDiffIndices << '\n';
    return 0;
}