#include <iostream>
#include <algorithm>

struct Triangle {
    Triangle() : a_(0), b_(0), c_(0) {}
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}
    Triangle(int (&a)[3]) : a_(a[0]), b_(a[1]), c_(a[2]) {}

    bool CorrectTriangle();
    bool IsRightTriangle();

    void Print();

    int a_, b_, c_;
};

bool Triangle::CorrectTriangle() {
    return a_ <= (b_ + c_);
}

bool Triangle::IsRightTriangle() {
    return a_* a_ == b_ * b_ + c_ * c_;
}

void Triangle::Print() {
    std::cout << a_ << ' ' << b_ << ' ' << c_ << '\n';
    return;
}

std::istream & operator>>(std::istream & is, Triangle & triangle) {
    int a[3];
    is >> a[0] >> a[1] >> a[2];
    std::sort(a, a + 3, std::greater<int>());
    triangle = Triangle(a);
    return is;
}

int main() {
    Triangle triangle;
    std::cin >> triangle;
    // triangle.Print();
    std::cout << (triangle.CorrectTriangle() 
                ? (triangle.IsRightTriangle() ? "YES" : "NO") 
                : "UNDEFINED") << '\n';
    return 0;
}