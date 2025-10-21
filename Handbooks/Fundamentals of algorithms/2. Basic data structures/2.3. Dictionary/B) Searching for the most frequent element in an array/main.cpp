#include <iostream>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    int maxFreq = 0, answer;
    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        ++mp[a];
        if (mp[a] >= maxFreq) {
            if (mp[a] == maxFreq && a >= answer) {
                continue;
            }
            
            answer = a;
            maxFreq = mp[a];
        }
    }

    std::cout << answer << '\n';
    return 0;
}