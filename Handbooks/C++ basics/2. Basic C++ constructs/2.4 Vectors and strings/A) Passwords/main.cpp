#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>


bool CorrectPassword (std::string & password) {
    if (std::any_of(password.begin(), password.end(), [](const char c){ return !(33 <= c && c <= 126); })){
        return false; // Пароль должен состоять из символов таблицы ASCII с кодами от 33 до 126
    }
    int n = password.size();
    if (!(8 <= n && n <= 14)){
        return false; // Пароль должен быть не короче 8 символов и не длиннее 14;
    }

    // Пароль должен быть из 4 классов символов — большие буквы, маленькие буквы, цифры, 
    // прочие символы — в пароле должны присутствовать не менее трёх любых.
    std::vector<bool> classes(4, false);
    for (const char c : password) {
        if (std::isalpha(c)) {
            // 0 индекс отвечает за наличие больших букв, 1 за наличие маленьких 
            classes[c != std::toupper(c)] = true; 
        } else if (std::isdigit(c)) {
            classes[2] = true;
        } else {
            classes[3] = true;
        }
    }
    if (std::accumulate(classes.begin(), classes.end(), 0) < 3) {
        return false;
    }
    return true;
}

int main() {
    std::string password;
    std::cin >> password;
    std::cout << (CorrectPassword(password) ? "YES" : "NO") << '\n';
    return 0;
}