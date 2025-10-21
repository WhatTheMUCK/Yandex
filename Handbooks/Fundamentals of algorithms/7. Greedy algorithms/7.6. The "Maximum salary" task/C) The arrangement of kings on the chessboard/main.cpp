#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int r, c;
    cin >> r >> c;

    if (r == 1 && c == 1) {
        cout << 0 << '\n';
        return 0;
    }

    if (r == 1 || c == 1) {
        int n = max(r, c);
        // На линии: каждые 3 клетки → 2 короля, но крайние должны иметь выход
        // Максимум = n - ceil(n / 3.0) = n - (n + 2) / 3
        cout << n - (n + 2) / 3 << '\n';
        return 0;
    }

    // Общий случай: 2D
    long long total = 1LL * r * c;
    long long empty = 1LL * ((r + 2) / 3) * ((c + 2) / 3);
    cout << total - empty << '\n';

    return 0;
}