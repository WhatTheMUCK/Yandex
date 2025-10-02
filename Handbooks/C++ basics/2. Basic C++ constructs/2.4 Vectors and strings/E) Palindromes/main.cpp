#include <iostream>
#include <algorithm>

bool palindrome(std::string & s) {
    int n = s.size();
    if (n < 2) {
        return true;
    }
    int rightIter = n / 2;
    int leftIter = rightIter - (n % 2 == 0 ? 1 : 0);
    for (; 0 <= leftIter && rightIter < n && s[rightIter] == s[leftIter]; --leftIter, ++rightIter);
    return (leftIter == -1 && rightIter == n);
}

int main() {
    std::string input;
    std::getline(std::cin, input);
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    std::cout << (palindrome(input) ? "YES" : "NO") << '\n';
}