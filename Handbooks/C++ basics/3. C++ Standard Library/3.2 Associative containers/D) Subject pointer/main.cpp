#include <iostream>
#include <map>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::string word;
    int page;
    std::map<int, std::set<std::string>> mp;
    for (int i = 0; i < n; ++i) {
        std::cin >> word >> page;
        mp[page].insert(word);
    }

    for (const auto & [page, words] : mp) {
        std::cout << page;
        for (const std::string & word : words) {
            std::cout << ' ' << word;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    return 0;
}