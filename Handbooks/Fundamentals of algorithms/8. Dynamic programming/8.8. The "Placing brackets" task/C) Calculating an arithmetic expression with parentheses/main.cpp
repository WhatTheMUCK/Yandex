#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <climits>

using ll = long long;

ll evaluate(const std::string& s, int l, int r, std::vector<std::vector<ll>>& memo) {
    if (l > r) return 0;
    if (memo[l][r] != LLONG_MAX) return memo[l][r];

    // Шаг 1: проверим, является ли всё выражение числом
    bool isNumber = true;
    for (int i = l; i <= r; ++i) {
        if (!isdigit(s[i])) {
            isNumber = false;
            break;
        }
    }
    if (isNumber) {
        ll num = 0;
        for (int i = l; i <= r; ++i) {
            num = num * 10 + (s[i] - '0');
        }
        return memo[l][r] = num;
    }

    // Шаг 2: проверим, можно ли убрать внешние скобки
    int balance = 0;
    bool canRemoveParen = false;
    if (s[l] == '(') {
        for (int i = l; i <= r; ++i) {
            if (s[i] == '(') balance++;
            else if (s[i] == ')') balance--;
            if (balance == 0) {
                if (i == r) {
                    canRemoveParen = true;
                }
                break;
            }
        }
    }

    if (canRemoveParen) {
        ll val = evaluate(s, l + 1, r - 1, memo);
        return memo[l][r] = val;
    }

    // Шаг 3: ищем операции на верхнем уровне (balance == 0)
    balance = 0;
    int bestOpPos = -1;
    char bestOp = 0;

    // Сначала ищем + и - (левоассоциативно — идём слева направо)
    for (int i = l; i <= r; ++i) {
        if (s[i] == '(') balance++;
        else if (s[i] == ')') balance--;
        else if (balance == 0 && (s[i] == '+' || s[i] == '-')) {
            bestOpPos = i;
            bestOp = s[i];
        }
    }

    if (bestOpPos == -1) {
        // Ищем *
        for (int i = l; i <= r; ++i) {
            if (s[i] == '(') balance++;
            else if (s[i] == ')') balance--;
            else if (balance == 0 && s[i] == '*') {
                bestOpPos = i;
                bestOp = s[i];
            }
        }
    }

    if (bestOpPos == -1) {
        return memo[l][r] = evaluate(s, l + 1, r - 1, memo);
    }

    ll leftVal = evaluate(s, l, bestOpPos - 1, memo);
    ll rightVal = evaluate(s, bestOpPos + 1, r, memo);

    ll result;
    if (bestOp == '+') result = leftVal + rightVal;
    else if (bestOp == '-') result = leftVal - rightVal;
    else if (bestOp == '*') result = leftVal * rightVal;
    else result = 0;

    return memo[l][r] = result;
}

int main() {
    std::string s;
    std::cin >> s;

    int n = static_cast<int>(s.size());
    std::vector<std::vector<ll>> memo(n, std::vector<ll>(n, LLONG_MAX));

    ll ans = evaluate(s, 0, n - 1, memo);
    std::cout << ans << '\n';

    return 0;
}