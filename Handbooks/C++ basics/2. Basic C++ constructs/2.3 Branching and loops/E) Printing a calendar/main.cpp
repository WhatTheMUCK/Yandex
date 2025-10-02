#include <iostream>
#include <sstream>
#include <iomanip>

void printArray(int * a, int N) {
    for (int i = 0; i < N; ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    return;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    int amountOfPositionsForDays = n + k - 1;
    int days[amountOfPositionsForDays];
    for (int i = 0; i < amountOfPositionsForDays; ++i) {
        if (i < n - 1) {
            days[i] = 0;
        } else {
            days[i] = i - (n - 2);
        }
    }
    // printArray(days, amountOfPositionsForDays);

    std::ostringstream oss;
    int amountOfRows = ((amountOfPositionsForDays) + 6) / 7;
    for (int i = 0; i < amountOfRows; ++i) {
        for (int j = 0; j < std::min(7, amountOfPositionsForDays - 7 * i); ++j) {
            if (j > 0) {
                oss << ' ';
            }

            int curIndex = i * 7 + j;

            if (days[curIndex] == 0) {
                oss << "  ";
            } else {
                oss << std::setw(2) << days[curIndex];
            }
        }
        oss << '\n';
    }
    std::cout << oss.str();
    return 0;
}