#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;

// Глобальный генератор
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int karger(const vector<pair<int, int>>& orig_edges, int n) {
    vector<pair<int, int>> edges = orig_edges;
    vector<int> label(n);
    for (int i = 0; i < n; ++i) label[i] = i; // сжатие путей не нужно, просто метки

    int vertices = n;
    while (vertices > 2) {
        // Удалим петли и выберем случайное ребро
        vector<pair<int, int>> clean;
        for (auto [u, v] : edges) {
            int lu = label[u], lv = label[v];
            if (lu != lv) {
                clean.emplace_back(lu, lv);
            }
        }
        edges = move(clean);
        if (edges.empty()) break; // граф несвязный — разрез 0

        // Случайное ребро
        uniform_int_distribution<int> dist(0, (int)edges.size() - 1);
        int idx = dist(rng);
        int u = edges[idx].first;
        int v = edges[idx].second;

        // Стягиваем v в u: все v → u
        for (int i = 0; i < n; ++i) {
            if (label[i] == v) {
                label[i] = u;
            }
        }
        vertices--;
    }

    // Считаем рёбра между двумя оставшимися компонентами
    vector<pair<int, int>> clean;
    for (auto [u, v] : orig_edges) {
        int lu = label[u], lv = label[v];
        if (lu != lv) {
            clean.emplace_back(lu, lv);
        }
    }
    return (int)clean.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        edges.emplace_back(u, v);
    }

    int best = INT_MAX;
    // Число запусков: ~ n*n*log(n) — но ограничим ради времени
    int trials = min(1000, (int)(n * n * 2)); // для n=200 → 80000, но ограничим

    // Однако 1000 — безопасный выбор
    trials = 1000;

    for (int t = 0; t < trials; ++t) {
        int cut = karger(edges, n);
        if (cut < best) best = cut;
    }

    cout << best << '\n';
    return 0;
}