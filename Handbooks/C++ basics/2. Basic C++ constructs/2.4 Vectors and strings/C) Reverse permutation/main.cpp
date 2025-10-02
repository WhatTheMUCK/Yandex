#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> guests(n);
    for (int i = 0; i < n; ++i) {
        int guestPlace;
        std::cin >> guestPlace;
        guests[guestPlace - 1] = i + 1;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << guests[i]  << ' ';
    }
    std::cout << '\n';
    return 0;
}