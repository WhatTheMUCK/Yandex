#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    int skill = a[k - 1];
    int w = 0, s = 0;
    for (int x : a) {
        if (x < skill) ++w;
        else if (x > skill) ++s;
    }

    int wins = 0;
    while (w > 0) {
        ++wins;
        --w; // k побеждает одного слабого

        int w_odd = w % 2;
        int s_odd = s % 2;

        if (w_odd && s_odd) {
            --w;      // смешанная пара: слабый проигрывает
            w_odd = 0;
        }

        w = w / 2 + w_odd;
        s = s / 2 + s_odd;
    }

    cout << wins << '\n';
    return 0;
}