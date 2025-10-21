#include <iostream>

long long combinations(int n, int k) {
    if (k > n) {
        return 0;
    }
    
    long long answer = 1;
    long long num = 1, denum = 1;
    for (int i = 1; i <= n; ++i) {
        if (i <= k) {
            denum *= i;
        } 

        if (i > (n - k)) {
            num *= i;
        }
    }
    answer = num / denum;
    return answer;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::cout << combinations(n, k) << '\n';
    return 0;
}