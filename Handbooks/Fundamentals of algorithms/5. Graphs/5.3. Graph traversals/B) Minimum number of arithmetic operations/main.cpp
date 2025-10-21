#include <iostream>
#include <queue>
#include <unordered_set>

const int MAX_VALUE = 200'000;

int main() {
    int x, y;
    std::cin >> x >> y;
    if (x == y) {
        std::cout << "0\n";
        return 0;
    }
    
    std::queue<std::pair<int, int>> BFS;
    std::unordered_set<long long> visited;
    std::string digits = "0123456789";

    BFS.push({x, 0});
    while (!BFS.empty()) {
        auto [parent, steps] = BFS.front();
        BFS.pop();

        ++steps;

        for (char digit : digits) {
            std::vector<long long> curVariants = {
                parent + (digit - '0'),
                parent - (digit - '0'),
                parent * (digit - '0')
            };
            for (long long variant : curVariants) {
                if (variant < 0 || variant > MAX_VALUE) {
                    continue;
                }

                if (visited.contains(variant)) {
                    continue;
                }

                if (variant == y) {
                    std::cout << steps << '\n';
                    return 0;
                }

                visited.insert(variant);
                BFS.push({variant, steps});
            }
        }
    }

    return 0;
}