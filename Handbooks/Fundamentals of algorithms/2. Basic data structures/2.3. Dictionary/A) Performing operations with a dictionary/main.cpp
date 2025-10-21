#include <iostream>
#include <unordered_map>

int main() {
    std::cin.tie(0);
    std::ios::sync_with_stdio(0);
    
    int q;
    std::cin >> q;
    std::unordered_map<int, int> mp;
    for (int i = 0; i < q; ++i) {
        int flag, x;
        std::cin >> flag >> x;
        if (flag == 1) {
            int y;
            std::cin >> y;
            mp[x] = y;
            continue;
        }

        int answer = mp[x];
        if (answer == 0) answer = -1;
        std::cout << answer << '\n';
    }
    return 0;
}