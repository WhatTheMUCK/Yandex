#include <iostream>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    long long result = 0;
    long long last = 0;
    long long current = 0;
    char op = '+'; // начальная операция

    for (int i = 0; i <= (int)s.size(); ++i) {
        char c = (i < (int)s.size()) ? s[i] : '+'; // фиктивная операция в конце

        if (isdigit(c)) {
            current = current * 10 + (c - '0');
        } else {
            if (op == '+') {
                result += current;
                last = current;
            } else if (op == '-') {
                result -= current;
                last = -current;
            } else if (op == '*') {
                result = result - last + last * current;
                last = last * current;
            }
            op = c;
            current = 0;
        }
    }

    std::cout << result << '\n';
    return 0;
}