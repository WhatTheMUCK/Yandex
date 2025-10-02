#include "logger.h"
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<Logger> container(n);
    for (int i = 0; i < n; ++i) {
        container.pop_back();
    }
    return 0;
}