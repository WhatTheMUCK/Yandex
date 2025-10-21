#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <limits>

int main() {
    int N, P, K;
    std::cin >> N >> P >> K;
    std::vector<int> w(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> w[i];
    }

    std::unordered_map<int, std::unordered_set<int>> connectivity;
    for (int i = 0; i < P; ++i) {
        int t;
        std::cin >> t;
        for (int j = 0; j < t; ++j) {
            int serverId;
            std::cin >> serverId;
            connectivity[i].insert(serverId - 1);
        }
    }

    std::vector<bool> mask(N, false);
    std::fill(mask.end() - K, mask.end(), true);
    long long minWaiting = std::numeric_limits<long long>::max();
    std::vector<int> bestServers;
    do {
        std::vector<bool> visited(N, false);
        std::vector<int> tempServers;
        int curWaiting = 0;
        for (int i = 0; i < N; ++i) {
            if (mask[i] == false) {
                continue;
            }

            tempServers.push_back(i);
            curWaiting += w[i];

            for (int j = 0; j < P; ++j) {
                if (visited[j]) {
                    continue;
                }

                if (connectivity[j].contains(i)) {
                    visited[j] = true;
                }
            }
        }

        int amountOfConnectedPeople = std::accumulate(visited.begin(), visited.end(), 0);
        if (amountOfConnectedPeople == P && curWaiting < minWaiting) {
            minWaiting = curWaiting;
            bestServers = tempServers;
        }
    } while(std::next_permutation(mask.begin(), mask.end()));

    if (bestServers.empty()) {
        std::cout << "No solutions\n";
    } else {
        std::cout << minWaiting << '\n';
        for (size_t i = 0; i < bestServers.size(); ++i) {
            if (i > 0) std::cout << ' ';
            std::cout << bestServers[i] + 1;
        }
        std::cout << '\n';
    }

    return 0;
}