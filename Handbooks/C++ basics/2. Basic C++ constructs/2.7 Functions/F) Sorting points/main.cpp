#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int SquareDistance() const {
        return x * x + y * y;
    }

    int x, y;
};

bool operator<(const Point & lhs, const Point & rhs) {
    return lhs.SquareDistance() < rhs.SquareDistance();
}

std::istream & operator>>(std::istream & is, Point & point) {
    return is >> point.x >> point.y;
}

std::ostream & operator<<(std::ostream & os, const Point & point) {
    return os << point.x << ' ' << point.y;
}

int main() {
    size_t n;
    std::cin >> n;
    std::vector<Point> vec(n);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    std::sort(vec.begin(), vec.end());
    for (size_t i = 0; i < n; ++i) {
        std::cout << vec[i] << '\n';
    }
    return 0;
}