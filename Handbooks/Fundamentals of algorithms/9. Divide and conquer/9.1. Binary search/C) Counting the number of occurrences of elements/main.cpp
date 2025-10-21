#include <iostream>
#include <vector>

std::istream & operator>>(std::istream & is, std::vector<int> & rhs) {
    for (size_t i = 0; i < rhs.size(); ++i) {
        is >> rhs[i];
    }
    return is;
}

int binarySearch(const std::vector<int> & data, int query) {
    int n = static_cast<int>(data.size());
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (data[m] >= query) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    return l;
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
        if (i > 0) std::cout << ' ';
        int l = binarySearch(k, q[i]);
        int r = binarySearch(k, q[i] + 1);
        if (l == n || k[l] != q[i]) {
            std::cout << "0";
            continue;
        } 

        std::cout << (r - l);
    }
    std::cout << '\n';    

    return 0;
}