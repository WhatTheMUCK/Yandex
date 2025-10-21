#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

long long merge_count(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    long long inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; ++i, ++k)
        arr[i] = temp[k];

    return inv_count;
}

long long merge_sort_count(vector<int>& arr, int left, int right) {
    long long inv_count = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;
        inv_count += merge_sort_count(arr, left, mid);
        inv_count += merge_sort_count(arr, mid + 1, right);
        inv_count += merge_count(arr, left, mid, right);
    }
    return inv_count;
}

long long count_inversions(vector<int> a) {
    return merge_sort_count(a, 0, (int)a.size() - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n);
    vector<int> pos(n + 1);

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    // Инверсии для x = 1
    long long current = count_inversions(p);
    long long best = current;

    // Перебираем x = 2 ... n
    for (int x = 2; x <= n; ++x) {
        int i = pos[x - 1]; // позиция элемента, который уходит в конец
        current += (n - 1 - 2LL * i);
        if (current < best) best = current;
    }

    cout << best << '\n';

    return 0;
}