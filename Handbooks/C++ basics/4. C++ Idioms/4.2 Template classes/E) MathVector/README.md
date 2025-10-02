# MathVector

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Математический вектор (не путать с `std::vector!`) — структура линейной алгебры, определяющаяся набором упорядоченных чисел (координат). Обозначается как `(x₁, x₂, ..., xₙ)`. Число `n` в таком случае называется **размерностью вектора**.

В качестве примера можно рассмотреть вектора размерности два с координатами в вещественных числах. В таком случае вектор `(1, 2)` будет задавать знакомый нам со школы геометрический вектор с началом в координате `(0, 0)` и концом в `(1, 2)`.

Также заметим, что координаты вектора необязательно вещественные числа. Это могут быть рациональные, комплексные или любые другие математические объекты, обладающие набором базовых операций сложения и умножения (например, математические матрицы).

---

### Над математическим вектором можно проводить две операции:

- **Сложение двух векторов одинаковой размерности**:  
  Пусть `a = (x₁, x₂, ..., xₙ)`, `b = (y₁, y₂, ..., yₙ)`, тогда  
  `a + b = (x₁ + y₁, x₂ + y₂, ..., xₙ + yₙ)`.

- **Умножение вектора на число** (тип числа должен быть одинаковым с типом координат вектора):  
  Пусть `c = (x₁, x₂, ..., xₙ)`, `α` — число, тогда  
  `α ⋅ c = (α⋅x₁, α⋅x₂, ..., α⋅xₙ)`.

---

### Вам дан шаблонный класс `MathVector<T>`, представляющий собой математический вектор с координатами типа `T`:

```cpp
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
        while (first != last) {
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
MathVector<T> operator * (const MathVector<T>& v, const T& scalar) {
    auto tmp(v);
    tmp *= scalar;
    return tmp;
}

template <typename T>
MathVector<T> operator * (const T& scalar, const MathVector<T>& v) {
    return v * scalar;
}
```

---

### Ваша задача:

Исправить ошибки в коде этого класса и **дописать операторы `+=` и `+` для сложения векторов**.  
Считайте, что складываться друг с другом всегда будут **только векторы одинаковой размерности**.

---

**Примечание**  
В вашем решении должен быть **только код класса** и не должно быть функции `main`.
## Решение

main.cpp
```cpp
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
```
