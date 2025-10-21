#include <iostream>
#include <algorithm>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;
    std::unordered_map<int, int> st;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int tmp;
            std::cin >> tmp;
            ++st[tmp];
        }
    }
    
    std::cout << std::count_if(st.begin(), st.end(), [n](const std::pair<const int, int> & cur){
        return cur.second == n;
    }) << '\n';
    return 0;
}