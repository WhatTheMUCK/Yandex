#include <iostream>

int main() {
    double centimeters, centimeters_to_inch = 2.54;
    std::cin >> centimeters;
    std::cout << centimeters / centimeters_to_inch << '\n';
    return 0;
}