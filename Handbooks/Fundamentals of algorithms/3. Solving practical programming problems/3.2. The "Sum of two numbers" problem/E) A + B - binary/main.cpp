#include <iostream>
#include <algorithm>


int main() {
    std::string A, B;
    std::cin >> A >> B;
    int aIndex = static_cast<int>(A.size()) - 1;
    int bIndex = static_cast<int>(B.size()) - 1;
    std::string answer;
    int acc = 0;
    for (; aIndex >= 0 || bIndex >= 0 || acc; --aIndex, --bIndex) {
        if (aIndex < 0 && bIndex < 0) {
            char curChar = '0' + acc % 2;
            answer.push_back(curChar);
            acc /= 2;
            continue;
        }

        if (aIndex < 0) {
            int cur = B[bIndex] - '0';
            char curChar = '0' + ((acc + cur) % 2);
            answer.push_back(curChar);
            acc = (acc + cur) / 2;
            continue;
        }

        if (bIndex < 0) {
            int cur = A[aIndex] - '0';
            char curChar = '0' + ((acc + cur) % 2);
            answer.push_back(curChar);
            acc = (acc + cur) / 2;
            continue;
        }
        int cur = (A[aIndex] - '0') + (B[bIndex] - '0');
        char curChar = '0' + ((acc + cur) % 2);
        answer.push_back(curChar);
        acc = (acc + cur) / 2;
    }

    std::reverse(answer.begin(), answer.end());
    std::cout << answer << '\n';

    return 0;
}