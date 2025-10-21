#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::string input;
    std::cin >> input;
    
    std::string answer;
    int l = 0, r = n - 1;
    while (l <= r) {
        if (input[l] <= input[r]) {
            answer.push_back(input[l]);
            ++l;
        } else {
            answer.push_back(input[r]);
            --r;
        }
    }

    std::cout << answer << '\n';
    return 0;
}