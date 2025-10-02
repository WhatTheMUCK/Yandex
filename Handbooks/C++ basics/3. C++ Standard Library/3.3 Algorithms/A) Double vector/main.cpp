#include <iostream>
#include <vector>

template <typename T>
void Duplicate(std::vector<T>& v) {
    size_t n = v.size();
    v.resize(n * 2);
    for (size_t i = 0; i < n; ++i) {
        v[n + i] = v[i];
    }
}

int main() {
    std::vector<int> v = {1, 2, 3};
    Duplicate(v);
    for (int i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ';
    } 
    std::cout << '\n';
    return 0;
}