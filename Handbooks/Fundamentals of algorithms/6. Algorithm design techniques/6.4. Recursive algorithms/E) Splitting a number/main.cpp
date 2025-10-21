#include <iostream>
#include <vector>

void partitions(int n, int max_part, std::vector<int> & current) {
    if (n == 0) {
        for (size_t i = 0; i < current.size(); ++i) {
            if (i > 0) std::cout << "+";
            std::cout << current[i];
        }
        std::cout << '\n';
        return;
    }

    for (int i = std::min(max_part, n); i >= 1; --i) {
        current.push_back(i);
        partitions(n - i, i, current);
        current.pop_back();
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> temp;
    partitions(n, n, temp);
    return 0;
}