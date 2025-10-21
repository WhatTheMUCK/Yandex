#include <iostream>
#include <deque>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::deque<int> dq;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int mode, x;
        std::cin >> mode;
        
        switch (mode)
        {
            case 1:
                std::cin >> x;
                dq.push_front(x);
                break;
            case 2:
                std::cin >> x;
                dq.push_back(x);
                break;
            case 3:
                if (dq.empty()) 
                    break;
                dq.pop_front();
                break;
            case 4:
                if (dq.empty()) 
                    break;
                dq.pop_back();
                break;
            default:
                break;
        }

        if (dq.empty()) {
            std::cout << "-1\n";
            continue;
        }

        std::cout << dq.front() << ' ' << dq.back() << '\n';
    }

    return 0;
}