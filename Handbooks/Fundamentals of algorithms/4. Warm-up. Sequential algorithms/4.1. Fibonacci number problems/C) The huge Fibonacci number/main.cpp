#include <iostream>
#include <vector>

int main() {
    long long n, m;
    std::cin >> n >> m;    
    if (n == 0) {
        std::cout << n << '\n';
        return 0;
    }

    std::vector<int> pizano = {0, 1};

    int prev = 0, cur = 1;
    while (pizano.size() == static_cast<size_t>(2) || (prev != 0 || cur != 1)) {
        int tmp = prev;
        prev = cur;
        cur = (prev + tmp) % m;
        pizano.push_back(cur);
    }

    // Убираем 0 1 последние
    pizano.pop_back();
    pizano.pop_back();

    int period = static_cast<int>(pizano.size());

    std::cout << pizano[n % period] << '\n';
    return 0;
}