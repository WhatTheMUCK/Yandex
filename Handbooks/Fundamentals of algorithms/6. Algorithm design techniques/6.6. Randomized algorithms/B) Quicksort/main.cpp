#include <iostream>
#include <vector>
#include <random>
#include <chrono>


static std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

size_t lomutoPartition(std::vector<int>& vec, size_t l, size_t r) {
    std::uniform_int_distribution<size_t> dist(l, r);
    size_t randomIndex = dist(rng);
    std::swap(vec[randomIndex], vec[r]);

    int pivot = vec[r];
    size_t i = l;
    for (size_t j = l; j < r; ++j) {
        if (vec[j] <= pivot) {
            std::swap(vec[i], vec[j]);
            ++i;
        }
    }
    std::swap(vec[i], vec[r]);
    return i;
}

void quickSort(std::vector<int>& vec, size_t l, size_t r) {
    if (l >= r) return;

    size_t p = lomutoPartition(vec, l, r);
    if (p > 0) {
        quickSort(vec, l, p - 1);
    }
    quickSort(vec, p + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    quickSort(vec, 0, n - 1);

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';

    return 0;
}