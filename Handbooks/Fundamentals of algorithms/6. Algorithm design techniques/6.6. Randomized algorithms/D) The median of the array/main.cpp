#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <chrono>


std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

int quickSelect(std::vector<long long>& arr, int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }

    int pivotIndex = std::uniform_int_distribution<int>(left, right)(rng);
    std::swap(arr[pivotIndex], arr[right]);

    long long pivot = arr[right];
    int i = left;
    for (int j = left; j < right; ++j) {
        if (arr[j] < pivot) {
            std::swap(arr[i], arr[j]);
            ++i;
        }
    }

    int j = i;
    for (int k = i; k < right; ++k) {
        if (arr[k] == pivot) {
            std::swap(arr[j], arr[k]);
            ++j;
        }
    }
    std::swap(arr[j], arr[right]);

    // Теперь:
    // [left, i)       — < pivot
    // [i, j]          — == pivot
    // (j, right]      — > pivot

    int leftCount = i - left;
    int equalCount = j - i + 1;

    if (k <= leftCount) {
        return quickSelect(arr, left, i - 1, k);
    } else if (k <= leftCount + equalCount) {
        return pivot;
    } else {
        return quickSelect(arr, j + 1, right, k - leftCount - equalCount);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    long long median;
    if (n % 2 == 1) {
        median = quickSelect(a, 0, n - 1, n / 2 + 1);
    } else {
        std::vector<long long> b = a;
        long long x = quickSelect(a, 0, n - 1, n / 2);
        long long y = quickSelect(b, 0, n - 1, n / 2 + 1);
        median = (x + y) / 2;
    }

    std::cout << median << '\n';

    return 0;
}