#include <iostream>
#include <string>
#include <set>

int main() {
    std::string path;
    std::set<std::string> answer;
    while (std::cin >> path) {
        size_t lastSlash = 0;
        while ((lastSlash  = path.find('/', lastSlash)) != std::string::npos) {
            ++lastSlash;
            answer.insert(path.substr(0, lastSlash));
        }
    }

    for (const std::string & elem : answer) {
        std::cout << elem << '\n';
    }

    return 0;
}