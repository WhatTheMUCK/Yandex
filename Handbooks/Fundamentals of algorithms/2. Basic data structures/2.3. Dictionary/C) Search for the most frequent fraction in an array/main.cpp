#include <iostream>
#include <unordered_map>
#include <numeric>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};


int main() {
    int n;
    std::cin >> n;
    int maxFreq = 0;
    std::pair<int, int >answer = std::numeric_limits<std::pair<int, int>>::max();
    std::unordered_map<std::pair<int, int>, int, PairHash> mp;
    for (int i = 0; i < n; ++i) {
        int num, denum;
        std::cin >> num >> denum;
        int gcd = std::gcd(num, denum);
        num /= gcd;
        denum /= gcd;
        std::pair<int, int> number = {num, denum};
        ++mp[number];
        if (maxFreq <= mp[number]) {
            if (maxFreq == mp[number] && number.first * answer.second >= answer.first * number.second) {
                continue;
            }
            answer = number;
            maxFreq = mp[number];
        }
    }

    std::cout << answer.first << ' ' << answer.second << '\n';

    return 0;
}