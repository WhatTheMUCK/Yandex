#include <iostream>
#include <unordered_set>

int main() {
    int n;
    std::cin >> n;
    std::unordered_set<int> answer;
    for (int i = 0; i < n; ++i) {
        int k;
        std::cin >> k;
        for (int j = 0; j < k; ++j) {
            int tmp;
            std::cin >> tmp;
            answer.insert(tmp);
        }
    }

    std::cout << answer.size() << '\n';
    
    return 0;
}