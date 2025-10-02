#include <iostream>
#include <unordered_map>
#include <string>
#include <algorithm>

// Вам требуется реализовать этот алгоритм. Он работает так:

// Первая буква слова сохраняется.
// В остальной части слова буквы a, e, h, i, o, u, w и y удаляются;
// Оставшиеся буквы заменяются на цифры от 1 до 6, причём похожим по звучанию буквам соответствуют одинаковые цифры:

// b, f, p, v: 1
// c, g, j, k, q, s, x, z: 2
// d, t: 3
// l: 4
// m, n: 5
// r: 6


std::unordered_map<char, int> mp;

void init() {
    for (const char c : "aehiouwy") {
        mp[c] = -1;
    }

    for (const char c : "bfpv") {
        mp[c] = 1;
    }

    for (const char c : "cgjkqsxz") {
        mp[c] = 2;
    }

    for (const char c : "dt") {
        mp[c] = 3;
    }

    mp['l'] = 4;

    for (const char c : "mn") {
        mp[c] = 5;
    }

    mp['r'] = 6;
}

int main() {
    init();
    std::string input;
    std::cin >> input;
    input.erase(std::remove_if(input.begin() + 1, input.end(), [](const char c){ return mp[c] == -1; }), input.end());
    for (size_t i = 1; i < input.size(); ++i) {
        input[i] = mp[input[i]] + '0';
    }
    input.erase(std::unique(input.begin(), input.end()), input.end());
    input.resize(4, '0');
    std::cout << input << '\n';
    return 0;
}