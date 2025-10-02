#include <iostream>
#include <vector>

struct Position {
    Position() : row_(0), col_(0) {}
    Position(int row, int col) : row_(row), col_(col) {}
    Position & operator+=(const Position & rhs);

    int row_, col_;
};

Position & Position::operator+=(const Position & rhs) {
    this->row_ += rhs.row_;
    this->col_ += rhs.col_;
    return *this;
}

Position operator+(Position lhs, const Position & rhs) {
    return (lhs += rhs);
}

std::istream & operator>>(std::istream & is, Position & pos) {
    return is >> pos.row_ >> pos.col_;
}

std::ostream & operator<<(std::ostream & os, const Position & pos) {
    return os << '(' << pos.row_ << ", " << pos.col_ << ')';
}


int main() {
    int m, n, k;
    std::cin >> m >> n >> k;
    std::vector<std::vector<char>> field(m + 2, std::vector<char>(n + 2, '0'));
    for (int i = 0; i < k; i++) {
        Position tempPos;
        std::cin >> tempPos;
        field[tempPos.row_][tempPos.col_] = '*'; 
    }

    std::vector<Position> offset = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};   
    for (int row = 1; row <= m; ++row) {
        for (int col = 1; col <= n; ++col) {
            if (field[row][col] == '*') {
                continue;
            }

            for (Position & curOffset : offset) {
                Position curPos = Position(row, col) + curOffset; 
                field[row][col] += (field[curPos.row_][curPos.col_] == '*'); 
            }
        }
    }

    for (int row = 1; row <= m; ++row) {
        for (int col = 1; col <= n; ++col) {
            std::cout << field[row][col] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}