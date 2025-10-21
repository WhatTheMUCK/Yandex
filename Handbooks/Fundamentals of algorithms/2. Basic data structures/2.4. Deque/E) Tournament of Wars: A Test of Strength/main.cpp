#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <unordered_map>


struct ListNode {
public:
    ListNode() : val(std::numeric_limits<int>::min()), next(this), prev(this) {}
    ListNode(int x) : val(x), next(this), prev(this) {}
    ListNode(int x, ListNode * nextt) : val(x), next(nextt) {}
    ListNode(int x, ListNode * nextt, ListNode * prevv) : val(x), next(nextt), prev(prevv) {}

    int val;
    ListNode * next;
    ListNode * prev;
};

void trio(ListNode * cur, std::string message = "") {
    std::cout << message << cur->prev->val << ' ' << cur->val << ' ' << cur->next->val << '\n';
    return;
}

int main() {
    int n;
    std::cin >> n;
    int wariorStrength;
    std::cin >> wariorStrength;
    ListNode * curWarior = new ListNode(wariorStrength);
    ListNode * tempWarior = curWarior;

    for (int i = 1; i < n; ++i) {
        std::cin >> wariorStrength;
        ListNode * temp = new ListNode(wariorStrength);
        tempWarior->next = temp;
        temp->prev = tempWarior;
        tempWarior = temp;
    }

    tempWarior->next = curWarior;
    curWarior->prev = tempWarior;

    if (n < 3) {
        std::cout << curWarior->val << ' ' << curWarior->next->val << '\n';
        return 0;
    }

    ListNode * prevWarior;
    while (n > 2) {
        prevWarior = curWarior;

        std::vector<int> strength = {curWarior->prev->val, curWarior->val, curWarior->next->val};
        std::vector<ListNode *> wariors = {curWarior->prev, curWarior, curWarior->next};
        const auto [minIter, maxIter] = std::minmax_element(strength.begin(), strength.end());
        int minIndex = minIter - strength.begin();
        int maxIndex = maxIter - strength.begin();
        if (maxIndex == 0) {
            curWarior = curWarior->prev;
        } else if (maxIndex == 2) {
            curWarior = curWarior->next;
        }

        ListNode * tracker = wariors[minIndex];

        if (tracker == prevWarior) {
            prevWarior = nullptr;
        }

        tracker->prev->next = tracker->next;
        tracker->next->prev = tracker->prev;
        delete tracker;

        --n;
    }

    if (prevWarior != nullptr) {
        std::cout << prevWarior->val << ' ' << prevWarior->next->val << '\n';
    } else {
        std::cout << curWarior->next->val << ' ' << curWarior->val << '\n';
    }

    return 0;
}