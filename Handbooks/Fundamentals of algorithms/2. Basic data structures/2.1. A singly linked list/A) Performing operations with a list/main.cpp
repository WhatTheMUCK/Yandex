#include <iostream>
#include <vector>


int main() {
    int q;
    std::cin >> q;
    std::vector<int> list;
    for (int i = 0; i < q; ++i) {
        int type, x;
        std::cin >> type >> x;
        if (type == 1) {
            int y;
            std::cin >> y;
            list.insert(list.begin() + x, y);
            continue;
        } 

        if (type == 2) {
            std::cout << list[x - 1] << '\n';
            continue;
        }

        if (type == 3) {
            list.erase(list.begin() + (x - 1));
        }
    }
    return 0;
}