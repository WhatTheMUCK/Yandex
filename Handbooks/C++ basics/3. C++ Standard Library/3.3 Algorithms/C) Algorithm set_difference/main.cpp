#include <iostream>
#include <set>
#include <vector>

template <typename InIter1, typename InIter2, typename OutIter>
OutIter SetDifference(InIter1 first1, InIter1 last1, InIter2 first2, InIter2 last2, OutIter out) {
    OutIter end = out;
    while (first1 != last1 && first2 != last2) {
        if (*first1 > *first2) {
            ++first2;
            continue;
        }

        if (*first1 == *first2) {
            ++first1;
            ++first2;
            continue;
        }

        if (*first1 < *first2) {
            *end = *first1;
            ++first1;
            ++end;
            continue;
        }
    }

    while (first1 != last1) {
        *end = *first1;
        ++first1;
        ++end;
    }

    return end;
}


int main() {
    std::vector<int> a = {1, 2, 2, 2, 3, 4, 6, 7, 7, 8};
    std::vector<int> b = {2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> ans;
    ans.reserve(20);
    SetDifference(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(ans));
    for (const auto & elem : ans) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
    return 0;
}