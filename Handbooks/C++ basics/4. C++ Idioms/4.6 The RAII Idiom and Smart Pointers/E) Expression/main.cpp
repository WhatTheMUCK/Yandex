#include <iostream>
#include <memory>
#include <string>

class Expression {
public:
    virtual int Evaluate() const = 0;
    virtual std::string ToString() const = 0;
    virtual ~Expression() {}
};

using ExpressionPtr = std::shared_ptr<Expression>;

// My code 
class ExpressionConst : public Expression {
public:
    ExpressionConst() = default;
    ExpressionConst(int val) : value(val) {}

    int Evaluate() const override {
        return value;
    }

    std::string ToString() const override {
        return std::to_string(value);
    }

private:
    int value;
};

ExpressionPtr Const(int x) {
    return ExpressionPtr(new ExpressionConst(x));
}

class BinaryOperation: public Expression {
protected:
    ExpressionPtr left;
    ExpressionPtr right;

public:
    BinaryOperation(ExpressionPtr l, ExpressionPtr r): left(l), right(r) {}
};

class ExpressionSum : public BinaryOperation {
public:
    ExpressionSum(ExpressionPtr l, ExpressionPtr r) : BinaryOperation(l, r) {}

    int Evaluate() const override {
        return left->Evaluate() + right->Evaluate();
    }

    std::string ToString() const override {
        return left->ToString() + " + " + right->ToString();
    }
};

ExpressionPtr Sum(ExpressionPtr l, ExpressionPtr r) {
    return ExpressionPtr(new ExpressionSum(l, r));
}

class ExpressionProduct: public BinaryOperation {
private:
    static std::string Parentheses(ExpressionPtr ex) {
        if (dynamic_cast<ExpressionSum *>(ex.get())) {
            return std::string("(") + ex->ToString() + ")";
        } else {
            return ex->ToString();
        }
    }

public:
    ExpressionProduct(ExpressionPtr l, ExpressionPtr r): BinaryOperation(l, r) {}

    int Evaluate() const override {
        return left->Evaluate() * right->Evaluate();
    }

    std::string ToString() const override {
        return Parentheses(left) + " * " + Parentheses(right);
    }
};

ExpressionPtr Product(ExpressionPtr l, ExpressionPtr r) {
    return ExpressionPtr(new ExpressionProduct(l, r));
}




int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
    return 0;
}