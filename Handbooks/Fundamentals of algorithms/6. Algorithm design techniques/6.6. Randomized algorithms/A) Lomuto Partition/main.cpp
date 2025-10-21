#include <iostream>
#include <vector>

void LomutoPartition(std::vector<int> & vec, size_t delimeterIndex) {
    std::vector<int> vecSmall, vecLarge;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == delimeterIndex) {
            continue;
        }

        if (vec[i] <= vec[delimeterIndex]) {
            vecSmall.push_back(vec[i]);
        } else {
            vecLarge.push_back(vec[i]);
        }
    }

    int delimeter = vec[delimeterIndex];
    for (size_t i = 0; i < vecSmall.size(); ++i) {
        vec[i] = vecSmall[i];
    }
    size_t curIndex = vecSmall.size();
    vec[delimeterIndex] = delimeter;
    ++curIndex;
    for (size_t i = 0; i < vecLarge.size(); ++i) {
        vec[curIndex + i] = vecLarge[i];
    }

    return;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    LomutoPartition(vec, 0);

    for (int i = 0; i < n; ++i) {
        if (i > 0) std::cout << ' ';
        std::cout << vec[i];
    }
    std::cout << '\n';

    return 0;
}