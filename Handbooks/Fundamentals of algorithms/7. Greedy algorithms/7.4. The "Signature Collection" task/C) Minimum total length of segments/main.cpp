#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> x(n);
    std::vector<unsigned int> distances(n - 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
        
    }
    std::sort(x.begin(), x.end());
    for (int i = 1; i < n; ++i) {
        distances[i - 1] = x[i] - x[i - 1];
    }

    if (k >= n) {
        std::cout << "0\n";
        return 0;
    }

    std::sort(distances.begin(), distances.end(), std::greater<int>());
    std::cout << std::accumulate(distances.begin() + (k - 1), distances.end(), 0ll) << '\n';

    return 0;
}