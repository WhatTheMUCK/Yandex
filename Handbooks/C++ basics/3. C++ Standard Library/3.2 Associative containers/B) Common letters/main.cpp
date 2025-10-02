#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main() {
    std::string input;
    int amountOfWords = 0;
    std::unordered_map<char, int> mp;
    while (std::cin >> input) {
        std::unordered_set<char> st(input.begin(), input.end());
        for (const char & c : st) {
            ++mp[c];
        }
        ++amountOfWords;
    }
    std::string answer;
    for (const auto & [key, value] : mp) {
        if (value == amountOfWords) {
            answer.push_back(key);
        }
    }
    std::sort(answer.begin(), answer.end());
    std::cout << answer << '\n';
    return 0;
}