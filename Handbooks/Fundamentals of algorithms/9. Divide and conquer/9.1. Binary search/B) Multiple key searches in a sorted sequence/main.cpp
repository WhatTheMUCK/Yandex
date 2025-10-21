#include <iostream>
#include <vector>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> k(n);
    std::cin >> k;
    
    std::cin >> m;
    std::vector<int> q(m);
    std::cin >> q;

    for (int i = 0; i < m; ++i) {
        int l = 0, r = n - 1;
        while (l < r) {
            int middle = (l + r) / 2;
            if (k[middle] == q[i]) {
                l = middle;
                break;
            }

            if (k[middle] < q[i]) {
                l = middle + 1;
            } else {
                r = middle - 1;
            }
        }

        if (l < n && k[l] == q[i]) {
            std::cout << l << '\n';
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}