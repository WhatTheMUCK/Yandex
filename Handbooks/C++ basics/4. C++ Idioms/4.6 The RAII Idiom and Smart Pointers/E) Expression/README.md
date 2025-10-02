# Выражение

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Представим арифметическое выражение, содержащее числовые константы и операции сложения и умножения, в виде дерева. В листьях этого дерева находятся константы, а в промежуточных узлах — операции.

Вам дан абстрактный базовый класс `Expression`:

```cpp
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
```

### Требуется реализовать:
- Классы-наследники для:
  - **константы**,
  - **сложения** (`Sum`),
  - **умножения** (`Product`).
- Функции `Const`, `Sum`, `Product`, возвращающие `ExpressionPtr`.

Эти функции и классы должны обеспечивать корректную работу следующего кода:

```cpp
#include "your_code.h"

int main() {
    ExpressionPtr ex1 = Sum(Product(Const(3), Const(4)), Const(5));
    std::cout << ex1->ToString() << "\n";  // 3 * 4 + 5
    std::cout << ex1->Evaluate() << "\n";  // 17

    ExpressionPtr ex2 = Product(Const(6), ex1);
    std::cout << ex2->ToString() << "\n";  // 6 * (3 * 4 + 5)
    std::cout << ex2->Evaluate() << "\n";  // 102
}
```

### Правила форматирования `ToString()`:
- При **умножении на сумму** сумма должна браться в скобки: `6 * (3 * 4 + 5)`.
- Для остальных случаев скобки **не требуются**.
- Не нужно обрабатывать специальные случаи с 0 или 1.

### Дополнительные требования:
- Используйте `std::to_string` для преобразования чисел в строки.
- Избегайте лишних копирований объектов — дерево должно строиться эффективно.
- Не должно быть утечек памяти.
- Сдайте **только ваш код** (реализацию классов и функций `Const`, `Sum`, `Product`), без `main` и без повторного определения `Expression`.
## Решение

main.cpp
```cpp
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
```
