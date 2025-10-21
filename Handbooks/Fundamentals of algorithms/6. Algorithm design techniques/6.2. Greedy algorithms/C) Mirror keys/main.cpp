#include <iostream>

int main() {
    int k, s;
    std::cin >> k >> s;
    if (k == 1) {
        std::cout << s << ' ' << s << '\n';
        return 0;
    }

    std::string key1(k, '0'), key2(k, '9');
    int l = 0, r = k - 1;
    int s1 = s;
    key1[l] = '1';
    key1[r] = '1';
    if (l == r) {
        --s1;
    } else {
        s1 -= 2;
    }

    l = (k - 1) / 2, r = k / 2;
    while (l >= 0 && r < k && s1 > 0) {
        if (l == r) {
            int value = std::min(s1, 9);
            if ((s % 2) != (value % 2)) {
                --value;
            }
            if (l == 0) {
                ++value;
            }
            key1[l] = value + '0';
            s1 -= value;
        } else {
            int value = std::min(s1, 9 * 2);
            if (l == 0) {
                value += 2;
            }
            key1[l] = value / 2 + '0';  
            key1[r] = value / 2 + '0';
            s1 -= (value / 2) * 2;
        }
        --l, ++r;
    }
    
    l = (k - 1) / 2, r = k / 2;
    int s2 = 9 * k - s;
    while (l >= 0 && r < k && s2 > 0) {
        if (l == r) {
            int value = std::min(s2, 9);
            if ((s % 2) != ((9 - value) % 2)) {
                --value;
            }
            key2[l] = (9 - value) + '0';
            s2 -= value;
        } else {
            int value = std::min(s2, 9 * 2);
            key2[l] = (9 - value / 2) + '0';  
            key2[r] = (9 - value / 2) + '0';
            s2 -= (value / 2) * 2;
        }
        --l, ++r;
    }
    std::cout << key1 << ' ' << key2 << '\n';

    return 0;
}