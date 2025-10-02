#include <iostream>

struct Position {
    int x, y;
};

std::istream & operator>>(std::istream & is, Position & rhs) {
    return is >> rhs.x >> rhs.y;
}

bool InOneRow(Position & lhs, Position & rhs) {
    return lhs.x == rhs.x;
}

bool InOneCol(Position & lhs, Position & rhs) {
    return lhs.y == rhs.y;
}

bool InOneDiag(Position & lhs, Position & rhs) {
    return std::abs(lhs.x - rhs.x) == std::abs(lhs.y - rhs.y);
}

int main() {
    Position firstPos, secondPos;
    std::cin >> firstPos >> secondPos;
    std::cout << ((InOneRow(firstPos, secondPos) || 
                   InOneCol(firstPos, secondPos) || 
                   InOneDiag(firstPos, secondPos)) ? "YES" : "NO") << '\n';
    return 0;
}