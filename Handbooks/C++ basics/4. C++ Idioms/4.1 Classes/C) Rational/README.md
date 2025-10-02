# Rational

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Напишите класс `Rational` (рациональное число).  

Конструктор класса должен получать на вход два числа типа `int` (числитель и знаменатель). Считайте, что по умолчанию числитель равен `0`, а знаменатель — `1`.

---

### Требования к классу:

- Переопределите **бинарные операторы**:  
  `+`, `-`, `*`, `/` — работающие как с другим `Rational`, так и с `int`.

- Переопределите **унарные операторы**:  
  `+`, `-`.

- Предусмотрите **функции-члены**:  
  `Numerator()` и `Denominator()` — возвращают числитель и знаменатель **несократимого представления** дроби (знаменатель всегда положительный).

- Переопределите **составные операторы присваивания**:  
  `+=`, `-=`, `*=`, `/=`.

- Переопределите **операторы сравнения**:  
  `==`, `!=`.

---

**Примечание**  
Используйте функцию `std::gcd` из стандартной библиотеки для сокращения дробей.
## Решение

main.cpp
```cpp
#include <iostream>
#include <numeric>


class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    Rational(int x) : numerator_(x), denominator_(1) {}
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        Normalize();
    }

    int Numerator() const { return numerator_; }
    int Denominator() const { return denominator_; }


    Rational operator+() const {
        return *this;
    }

    Rational & operator+=(const Rational & rhs) {
        numerator_ = numerator_ * rhs.Denominator() + rhs.Numerator() * denominator_;
        denominator_ *= rhs.Denominator();
        Normalize();
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    Rational & operator-=(const Rational & rhs) {
        return *this += -rhs;
    }

    Rational & operator*=(const Rational & rhs) {
        numerator_ *= rhs.Numerator();
        denominator_ *= rhs.Denominator();
        Normalize();
        return *this;
    }

    Rational & operator/=(const Rational & rhs) {
        numerator_ *= rhs.Denominator();
        denominator_ *= rhs.Numerator();
        Normalize();
        return *this;
    }

private:
    int numerator_, denominator_;

    void Normalize() { 
        if (denominator_ == 0) {
            throw std::runtime_error("Деление на ноль недопустимо!");
        }

        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }

        int gcd = std::gcd(numerator_, denominator_); 
        numerator_ /= gcd;
        denominator_ /= gcd;
    }
};

bool operator==(const Rational & lhs, const Rational & rhs) {
    return (lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator());
}

bool operator!=(const Rational & lhs, const Rational & rhs) {
    return !(lhs == rhs);
}

Rational operator+(Rational lhs, const Rational & rhs) {
    return lhs += rhs;
}

Rational operator-(Rational lhs, const Rational & rhs) {
    return lhs -= rhs;
}

Rational operator*(Rational lhs, const Rational & rhs) {
    return lhs *= rhs;
}

Rational operator/(Rational lhs, const Rational & rhs) {
    return lhs /= rhs;
}

std::ostream & operator<<(std::ostream & os, const Rational & rhs) {
    return os << rhs.Numerator() << '/' << rhs.Denominator();
}

int main() {
    Rational a, b(1, 4);
    std::cout << a << '\n' << b << "\n\n";
    //std::cout << -a << ' ' << -b << '\n';
    std::cout << (a - 1) << ' ' << (a + 2) << ' ' << (a * 3) << ' ' << (a / 7) << '\n';
    return 0;
}
```
