#include <iostream>
#include <unordered_set>

int main() {
    int n;
    std::unordered_set<int> sequence;
    while (std::cin >> n) {
        const auto & [iter, has_insert] = sequence.insert(n);
        std::cout << (has_insert ? "NO" : "YES") << '\n';
    }
    return 0;
}