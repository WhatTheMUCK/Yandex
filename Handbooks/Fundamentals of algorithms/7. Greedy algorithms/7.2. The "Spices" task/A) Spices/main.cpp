#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>


int main() {
    int n, W;
    std::cin >> n >> W;
    std::vector<std::pair<int, int>> species(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> species[i].first >> species[i].second;
    }
    std::sort(species.begin(), species.end(), [](const auto & lhs, const auto & rhs){
        return 1ll * lhs.first * rhs.second > 1ll * rhs.first * lhs.second;
    });

    double answer = 0;
    for (size_t curSpeciesIndex = 0; W > 0 && curSpeciesIndex < species.size(); ++curSpeciesIndex) {
        int amount = std::min(W, species[curSpeciesIndex].second);
        W -= amount;
        if (amount == species[curSpeciesIndex].second) {
            answer += species[curSpeciesIndex].first;
        } else {
            answer += amount * ((1.0 * species[curSpeciesIndex].first) / species[curSpeciesIndex].second);
        }
    }
    std::cout << std::fixed << std::setprecision(4) << answer << '\n';

    return 0;
}