#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    int n, k, w;
    std::cin >> n >> k >> w;
    std::vector<std::pair<int, int>> advertisers(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> advertisers[i].first >> advertisers[i].second;
    }
    std::sort(advertisers.begin(), advertisers.end(), std::greater<std::pair<int, int>>());
    long long answer = 0;
    int curBillBoard = 0, curWeak = 0, curAdvertiser = 0;
    while (curBillBoard < n && curAdvertiser < k) {
        int amountOfWeaks = std::min(w, advertisers[curAdvertiser].second);
        curWeak += amountOfWeaks;
        curBillBoard += (curWeak / w);
        curWeak %= w;
        answer += 1ll * amountOfWeaks * advertisers[curAdvertiser].first;
        ++curAdvertiser;
    }

    if (curBillBoard == n) {
        --curAdvertiser;
        answer -= curWeak * advertisers[curAdvertiser].first;
    }

    std::cout << answer << '\n';
    
    return 0;
}