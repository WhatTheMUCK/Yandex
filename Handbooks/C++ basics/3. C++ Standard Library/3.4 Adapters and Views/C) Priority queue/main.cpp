#include <iostream>
#include <vector>
#include <queue>

int main() {
    std::priority_queue<int> pq;
    std::string request;
    while (std::cin >> request) {
        if (request == "CLEAR") {
            pq = std::priority_queue<int>();
            continue;
        }

        if (request == "ADD") {
            int n;
            std::cin >> n;
            pq.push(n);
            continue;
        }

        if (request == "EXTRACT") {
            if (pq.empty()) {
                std::cout << "CANNOT\n";
                continue;
            }

            std::cout << pq.top() << '\n';
            pq.pop();
            continue;
        }
    }
    return 0;
} 