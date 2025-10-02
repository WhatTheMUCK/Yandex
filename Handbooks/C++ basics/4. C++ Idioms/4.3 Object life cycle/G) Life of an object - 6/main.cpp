#include "logger.h"
#include <deque>

int main() {
    int n;
    std::cin >> n;
    std::deque<Logger> container(n);
    for (int i = 0; i < n; ++i) {
        container.pop_front();
    }
    return 0;
}