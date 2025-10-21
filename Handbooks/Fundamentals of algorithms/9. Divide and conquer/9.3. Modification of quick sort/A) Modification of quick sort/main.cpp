#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

std::mt19937 rng(std::random_device{}());

std::vector<int> randomizedQuickSort(const std::vector<int>& a) {
    if (a.size() <= 1) {
        return a;
    }

    // Выбираем случайный опорный элемент
    int pivot = a[std::uniform_int_distribution<int>(0, a.size() - 1)(rng)];

    std::vector<int> less, equal, greater;
    for (int x : a) {
        if (x < pivot) {
            less.push_back(x);
        } else if (x == pivot) {
            equal.push_back(x);
        } else {
            greater.push_back(x);
        }
    }

    // Рекурсивно сортируем меньшие и большие
    auto sorted_less = randomizedQuickSort(less);
    auto sorted_greater = randomizedQuickSort(greater);

    // Собираем результат
    sorted_less.insert(sorted_less.end(), equal.begin(), equal.end());
    sorted_less.insert(sorted_less.end(), sorted_greater.begin(), sorted_greater.end());

    return sorted_less;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    auto result = randomizedQuickSort(a);

    for (size_t i = 0; i < result.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << result[i];
    }
    std::cout << '\n';

    return 0;
}