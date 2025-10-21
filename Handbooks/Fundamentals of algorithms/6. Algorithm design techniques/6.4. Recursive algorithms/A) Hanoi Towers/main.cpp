#include <iostream>
#include <vector>
#include <functional>

struct HanoiTowersState {
    int remainded;
    int fromPillar;
    int toPillar;

    bool operator==(const HanoiTowersState & other) const {
        return remainded == other.remainded &&
               fromPillar == other.fromPillar &&
               toPillar == other.toPillar;
    }
};

namespace std {
    template<>
    struct hash<HanoiTowersState> {
        size_t operator()(const HanoiTowersState & s) const {
            return hash<int>()(s.remainded) ^
                   (hash<int>()(s.fromPillar) << 1) ^
                   (hash<int>()(s.toPillar) << 2);
        }
    };
}

std::unordered_map<HanoiTowersState, std::vector<std::pair<int, int>>> states;

std::vector<std::pair<int, int>> HanoiTowers(int n, int fromPillar, int toPillar) {
    HanoiTowersState cur = {n, fromPillar, toPillar};
    if (states.contains(cur)) {
        return states[cur];
    }
    
    if (n == 1) {
        states[cur] = {{fromPillar, toPillar}};
        return states[cur];
    }

    int intermediatePillar = 6 - fromPillar - toPillar;
    states[cur] = HanoiTowers(n - 1, fromPillar, intermediatePillar);
    states[cur].push_back({fromPillar, toPillar});
    std::vector<std::pair<int, int>> temp = HanoiTowers(n - 1, intermediatePillar, toPillar);
    for (const std::pair<int, int> & step : temp) {
        states[cur].push_back(step);
    }
    return states[cur];
}   

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> answer = HanoiTowers(n, 1, 3);
    std::cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); ++i) {
        std::cout << answer[i].first << ' ' << answer[i].second << '\n';
    }
    return 0;
}