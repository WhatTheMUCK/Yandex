#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::unordered_map<int, int> candidates;

    for (int x : a) {
        if (candidates.count(x)) {
            candidates[x]++;
        }

        else if (static_cast<int>(candidates.size()) < 3) {
            candidates[x] = 1;
        }

        else {
            std::vector<int> toErase;
            for (auto& [key, cnt] : candidates) {
                cnt--;
                if (cnt == 0) {
                    toErase.push_back(key);
                }
            }
            for (int key : toErase) {
                candidates.erase(key);
            }
        }
    }


    std::unordered_map<int, int> freq;
    for (int x : a) {
        if (candidates.count(x)) {
            freq[x]++;
        }
    }

    int count = 0;
    for (auto& [val, f] : freq) {
        if (f > n / 4) {
            count++;
        }
    }

    std::cout << (count >= 3 ? 1 : 0) << '\n';

    return 0;
}