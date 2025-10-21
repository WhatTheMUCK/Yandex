#include <iostream>

int main() {
    std::string input, temp;
    std::cin >> input >> temp;
    std::cout << (input.find(temp) != std::string::npos ? "YES" : "NO") << '\n';
    return 0;
}