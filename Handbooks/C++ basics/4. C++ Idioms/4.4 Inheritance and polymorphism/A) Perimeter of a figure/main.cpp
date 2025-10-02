class Figure {
public:
    virtual int Perimeter() const = 0;
    virtual ~Figure() {};
};

class Triangle : public Figure {
public:
    Triangle(int a, int b, int c) : a_(a), b_(b), c_(c) {}

    int Perimeter() const override {
        return a_ + b_ + c_;
    }

private:
    int a_, b_, c_;
};

class Rectangle : public Figure {
public:
    Rectangle(int a, int b) : a_(a), b_(b) {}

    int Perimeter() const override {
        return 2 * (a_ + b_);
    }

private:
    int a_, b_;
};

#include <vector>
#include <iostream>

int main() {
    std::vector<Figure*> figures;

    std::string type;

    while (std::cin >> type) {
        if (type == "Triangle") {
            int a, b, c;
            std::cin >> a >> b >> c;
            figures.push_back(new Triangle(a, b, c));
        } else if (type == "Rectangle") {
            int a, b;
            std::cin >> a >> b;
            figures.push_back(new Rectangle(a, b));
        }
    }

    for (Figure* f : figures) {
        std::cout << f->Perimeter() << "\n";
    }

    for (Figure* f : figures) {
        delete f;
    }
}