#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<bool>> meatingRooms(n, std::vector<bool>(601, false));
    int deviations = 0;
    for (int i = 0; i < m; ++i) {
        int start, time;
        std::cin >> start >> time;
        bool haveMeatingRoom = false;
        for (int j = 0; j < n && !haveMeatingRoom; ++j) {
            bool canBe = true;
            for (int k = start; k < start + time; ++k) {
                if (meatingRooms[j][k] == true) {
                    canBe = false;
                    break;
                }
            }

            if (!canBe) {
                continue;
            }

            haveMeatingRoom = true;
            for (int k = start; k < start + time; ++k) {
                meatingRooms[j][k] = true;
            }
        }
        // std::cout << std::boolalpha;
        // std::cout << "i = " << i << " | " << start << ' ' << time << ' ' << haveMeatingRoom << '\n';
        deviations += !haveMeatingRoom;
    }

    std::cout << deviations << '\n';
    return 0;
}