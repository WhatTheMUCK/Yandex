#include <iostream>
#include <string>
#include <deque>


void MakeTrain() {
    char flag;
    std::string direction;
    size_t number;
    std::deque<int> cars;
    while (std::cin >> flag >> direction >> number) {
        if (flag == '+') {
            direction == "left" ? cars.push_front(number) : cars.push_back(number);
        } else {
            if (number >= cars.size()) {
                cars.clear();
                continue;
            }

            direction == "left" ? cars.erase(cars.begin(), cars.begin() + number) 
                                : cars.erase(cars.end() - number, cars.end());
        }
    }

    for (const int elem : cars) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
    return;
}

int main() {
    MakeTrain();
    return 0;
}