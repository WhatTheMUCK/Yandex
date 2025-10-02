#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> Split(const std::string & str, char delimiter) {
    std::vector<std::string> answer;
    size_t curPos = 0, nextPos = std::string::npos;
    while ((nextPos = str.find(delimiter, nextPos + 1)) != std::string::npos) {
        answer.push_back(str.substr(curPos, nextPos - curPos));
        curPos = nextPos + 1;
    }
    answer.push_back(str.substr(curPos));

    return answer;
}

std::ostream & operator<<(std::ostream & os, const std::vector<std::string> & vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        os << i << ": " << vec[i] << '\n';
    }
    return os;
}

int main() {
    std::string input;
    char delimiter;
    std::cout << Split("", ' ') << '\n';
    std::cin >> input >> delimiter;
    std::cout << Split(input, delimiter) << '\n';
    return 0;
}