#include <iostream>
#include <vector>
#include <numeric>

template <typename T>
class Polynomial {
public:
    Polynomial() = default;
    Polynomial(const std::vector<T> & data) : data_(data) { Normalize(); }
    Polynomial(const T & value) : data_{value} { Normalize(); }

    template <typename Iterator>
    Polynomial(Iterator IterStart, Iterator IterEnd) : data_{IterStart, IterEnd} { Normalize(); }

    const std::vector<T>& GetCoefficients() const {
        return data_;
    }

    std::vector<T>& GetCoefficients() {
        return data_;
    }

    friend bool operator==(const Polynomial<T> & lhs, const Polynomial<T> & rhs) {
        return lhs.GetCoefficients() == rhs.GetCoefficients();
    }

    friend bool operator!=(const Polynomial<T> & lhs, const Polynomial<T> & rhs) {
        return !(lhs == rhs);
    }

    Polynomial<T> & operator+=(const Polynomial<T> & other) {
        if (other.data_.size() > data_.size()) {
            data_.resize(other.data_.size());
        }

        for (size_t i = 0; i < other.data_.size(); ++i) {
            data_[i] += other.data_[i];
        }

        Normalize();

        return *this;
    }


    Polynomial<T> & operator-=(const Polynomial<T> & other) {
        if (other.data_.size() > data_.size()) {
            data_.resize(other.data_.size());
        }

        for (size_t i = 0; i < other.data_.size(); ++i) {
            data_[i] -= other.data_[i];
        }

        Normalize();

        return *this;
        // Руки чешутся сделать просто return *this += -other,
        // но также не хочется сложность приводить к 2n, вместо 1n
    }

    Polynomial<T> & operator*=(const Polynomial<T> & other) {
        if (data_.empty() || other.data_.empty()) {
            data_.resize(0);
            return *this;
        }

        std::vector<T> answer(data_.size() + other.data_.size() - 1);
        
        for (size_t i = 0; i < data_.size(); ++i) {
            for (size_t j = 0; j < other.data_.size(); ++j) {
                answer[i + j] += data_[i] * other.data_[j];
            }
        }

        data_ = std::move(answer);

        Normalize();

        return *this;
    }

    friend Polynomial<T> operator+(Polynomial<T> lhs, const Polynomial<T> & rhs) {
        return lhs += rhs;
    }

    friend Polynomial<T> operator-(Polynomial<T> lhs, const Polynomial<T> & rhs) {
        return lhs -= rhs;
    }

    friend Polynomial<T> operator*(Polynomial<T> lhs, const Polynomial<T> & rhs) {
        return lhs *= rhs;
    }

    int Degree() const {
        return data_.size() - 1;
    }

    const T& operator[] (int degree) const {
        if (degree > Degree()) {
            return valueTypeZero;
        }

        return data_[degree];
    }

    T operator() (const T & value) const {
        T result = valueTypeZero;
        for (int i = Degree(); i >= 0; --i) {
            result *= value;
            result += data_[i];
        }

        return result;
    }

    auto begin() const {
        return data_.cbegin();
    }

    auto end() const {
        return data_.cend();
        // Я при любых изменениях вызываю Normalize() которая избавляется от всех лишних 0 у старших степней
    }

private:
    std::vector<T> data_;
    inline static const T valueTypeZero{0};
    
    void Normalize() {
        while (!data_.empty() && (data_.back() == 0)) {
            data_.pop_back();
        }
        return;
    }
};

template <typename T>
std::ostream & operator<<(std::ostream & os, const Polynomial<T> & polynom) {
    for (int i = polynom.Degree(); i >= 0; --i) {
        os << polynom[i];
        if (i != 0) {
            os << ' ';
        }
    }
    return os;
}

void TestConstructs() {
    Polynomial<double> polynom({1.3, 2, 3, 4});
    std::cout << polynom << '\n';
    // Polynomial<double> polynom2(15);
    std::cout << Polynomial<double>(15) << '\n';
    std::cout << Polynomial<double>() << '\n';
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::cout << Polynomial<double>(alphabet.begin(), alphabet.end()) << '\n';
    return;
}


int main() {
    Polynomial<double> polynom({1.3, 2, 3, 4});
    Polynomial<double> polynom2({0, 0, 1, 0});
    std::cout << std::boolalpha << (Polynomial<double>({1, 2, 0}) == Polynomial<double>({1, 2, 0, 0})) << '\n';
    std::cout << (Polynomial<double>({0, 0, 0, 0, 1}) == 1) << '\n';
    std::cout << (5 != Polynomial<char>(5)) << '\n';
    std::cout << polynom(2) << '\n';
    std::cout << *(polynom.end() - 1) << '\n';
    std::cout << '\n' << (polynom * polynom2) << '\n';
    std::cout << polynom2(3) << '\n';
    std::cout << (polynom2 += 10) << '\n';
    return 0;
}