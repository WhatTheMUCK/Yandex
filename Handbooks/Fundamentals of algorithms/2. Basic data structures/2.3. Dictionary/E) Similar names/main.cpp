#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::unordered_map<std::string, long long> freq;
    std::string word;
    for (int i = 0; i < n; ++i) {
        std::cin >> word;
        ++freq[word];
    }

    std::unordered_map<std::string, long long> totalForMask;
    std::unordered_map<std::string, long long> sumSqForMask;

    for (const auto & [w, cnt] : freq) {
        std::string s = w;
        for (size_t i = 0; i < s.size(); ++i) {
            char orig = s[i];
            s[i] = '*';
            totalForMask[s] += cnt;
            sumSqForMask[s] += cnt * cnt;
            s[i] = orig;
        }
    }

    long long answer = 0;
    for (const auto& [mask, total] : totalForMask) {
        const long long & sum_sq = sumSqForMask[mask];
        answer += (total * total - sum_sq) / 2;
    }

    std::cout << answer << '\n';
    return 0;
}