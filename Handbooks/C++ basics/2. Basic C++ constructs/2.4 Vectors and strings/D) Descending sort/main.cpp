#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> container;
    std::string temp;   
    while (std::getline(std::cin, temp)) {
        container.push_back(temp);
    }
    std::sort(container.begin(), container.end(), std::greater<std::string>());
    for (const std::string & elem : container) {
        std::cout << elem << '\n';
    }
    return 0;
}