#include <iostream>
#include <vector>


int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n), maximum(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
        
        if (i > 0) {
            maximum[i] = maximum[i - 1];
            if (vec[i] >= vec[maximum[i]]) {
                maximum[i] = i;
            }
        }
    }    
    vec.erase(vec.begin() + maximum.back());

    --n;
    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';

    return 0;
}