#include <iostream>
#include <vector>

template <typename T>
class MathVector {
 private:
    std::vector<T> data;

 public:
    // Храним в `data` нулевой вектор длины `n`
    MathVector(size_t n) {
        data.resize(n);
    }

    template <typename Iter>
    MathVector(Iter first, Iter last) {
        for (;first != last; ++first) {
            data.push_back(*first);
        }
    }

    size_t Dimension() const {
         return data.size();
    }

    T& operator [] (size_t i) {
        return data[i];
    }

    const T& operator [] (size_t i) const {
        return data[i];
    }
};

// Output format: (1, 2, 3, 4, 5)
template <typename T>
std::ostream& operator << (std::ostream& out, const MathVector<T>& v) {
    out << '(';
    for (size_t i = 0; i != v.Dimension(); ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << v[i];
    }
    out << ')';
    return out;
}

template <typename T>
MathVector<T>& operator *= (MathVector<T>& v, const T& scalar) {
    for (size_t i = 0; i != v.Dimension(); ++i) {
        v[i] *= scalar;
    }
    return v;
}

template <typename T>
MathVector<T> operator * (MathVector<T> v, const T& scalar) {
    return v *= scalar;
}

template <typename T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& v) {
    return v * scalar;
}

template <typename T>
MathVector<T>& operator += (MathVector<T>& v, const MathVector<T>& other) {
    for (size_t i = 0; i != v.Dimension(); ++i) {
        v[i] += other[i];
    }
    return v;
}

template <typename T>
MathVector<T>& operator + (MathVector<T> v, const MathVector<T>& other) {
    return v += other;
}

int main() {
    std::vector<int> tmp = {1, 2, 3, 4, 5};
    MathVector<int> a1(tmp.begin(), tmp.end());
    std::cout << a1 << '\n';
    std::vector<int> tmp2 = {1, 0, 0, 0, 1};
    MathVector<int> a2(tmp2.begin(), tmp2.end());
    std::cout << a2 << '\n';
    std::cout << '\n' << (a2 *= 5) << '\n';
    std::cout << '\n' << (a1 + a2) << '\n';
    std::cout << a1.Dimension() << ' ' << a1[0] << ' ' << a1[4] << '\n';
    return 0;
}