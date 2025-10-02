#include <iostream>
#include <stack>
#include <unordered_map>

int main() {
    std::unordered_map<char, char> mp = {
        {'(', ')'},
        {'[', ']'},
        {'{', '}'}
    };
    std::stack<char> parenthesis;
    char curChar;
    while (std::cin >> curChar) {
        if (!parenthesis.empty() && mp.contains(parenthesis.top()) && mp[parenthesis.top()] == curChar) {
            parenthesis.pop();
            continue;
        }

        parenthesis.push(curChar);
    }

    std::cout << (parenthesis.empty() ? "YES" : "NO") << '\n';
    return 0;
}