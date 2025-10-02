# Коварная матрица

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Ваш друг пишет свою реализацию шаблонного класса «Матрица»:

```cpp
#include <iostream>

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows, columns;

public:
    Matrix(size_t m, size_t n): rows(m), columns(n) {
        data = new T * [rows];
        size_t i = 0;
        try {
            for (; i != rows; ++i) {
                data[i] = new T[columns];
            }
        } catch (...) {
            for (size_t k = 0; k != i; ++k) {
                delete [] data[k];
            }
            delete [] data;
            throw;
        }
    }

    T* operator [](size_t i) {
        return data[i];
    }
    const T* operator [](size_t i) const {
        return data[i];
    }

    size_t GetRows() const {
        return rows;
    }

    size_t GetColumns() const {
        return columns;
    }

    ~Matrix() {
        for (size_t i = 0; i != rows; ++i) {
            delete [] data[i];
        }
        delete [] data;
    }

    // Сюда можно будет вставить ваш код
    #include "your_code.h"
};
```

Также определены вспомогательные функции:

```cpp
template <typename T>
Matrix<T> FillMatrix(size_t m, size_t n) {
    Matrix<T> A(m, n);
    for (size_t i = 0; i != m; ++i) {
        for (size_t j = 0; j != n; ++j) {
            A[i][j] = i + j;
        }
    }
    return A;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& A) {
    for (size_t i = 0; i != A.GetRows(); ++i) {
        for (size_t j = 0; j != A.GetColumns(); ++j) {
            out << A[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
```

Однако следующий код **не компилируется** или **работает некорректно**:

```cpp
#include "matrix.h"
#include <iostream>

int main() {
    size_t m, n;
    std::cin >> m >> n;
    Matrix<int> A(m, n);
    // ...
    A = FillMatrix<int>(m, n);
    std::cout << A << "\n";
}
```

### Задача

Вам разрешено **только дописывать код** в месте `#include "your_code.h"` внутри класса `Matrix`.

Нужно реализовать недостающие операции, чтобы приведённый выше `main` заработал корректно.

### Важное примечание

Программа компилируется с флагом `-fno-elide-constructors`, что **отключает copy elision**. Это означает, что при возврате объекта из `FillMatrix` и при присваивании `A = ...` будут **обязательно вызваны**:
- конструктор копирования,
- оператор присваивания.

Если они не определены — поведение будет некорректным (двойное освобождение памяти, утечки и т.п.).

> Сдайте **только недостающий код**, который должен быть вставлен в `#include "your_code.h"`. Не дублируйте уже существующий код класса.
## Решение

matrix.h
```cpp
#include <iostream>

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows, columns;

public:
    Matrix(size_t m, size_t n): rows(m), columns(n) {
        data = new T * [rows];
        size_t i = 0;
        try {
            for (; i != rows; ++i) {
                data[i] = new T[columns];
            }
        } catch (...) {
            for (size_t k = 0; k != i; ++k) {
                delete [] data[k];
            }
            delete [] data;
            throw;
        }
    }

    T* operator [](size_t i) {
        return data[i];
    }
    const T* operator [](size_t i) const {
        return data[i];
    }

    size_t GetRows() const {
        return rows;
    }

    size_t GetColumns() const {
        return columns;
    }

    ~Matrix() {
        for (size_t i = 0; i != rows; ++i) {
            delete [] data[i];
        }
        delete [] data;
    }

    // Мой код
    Matrix(const Matrix & other) : rows(other.GetRows()), columns(other.GetColumns()) {
        data = new T * [rows];
        size_t i = 0;
        try {
            for (; i != rows; ++i) {
                data[i] = new T[columns];
                for (size_t j = 0; j != columns; ++j) {
                    data[i][j] = other[i][j];
                }
            }
        } catch (...) {
            for (size_t k = 0; k != i; ++k) {
                delete [] data[k];
            }
            delete [] data;
            throw;
        }
    }

    Matrix & operator=(const Matrix & other) {
        this->~Matrix();
        rows = other.GetRows(), columns = other.GetColumns();
        data = new T * [rows];
        size_t i = 0;
        try {
            for (; i != rows; ++i) {
                data[i] = new T[columns];
                for (size_t j = 0; j != columns; ++j) {
                    data[i][j] = other[i][j];
                }
            }
        } catch (...) {
            for (size_t k = 0; k != i; ++k) {
                delete [] data[k];
            }
            delete [] data;
            throw;
        }
        return *this;
    }
    // ...
};

template <typename T>
Matrix<T> FillMatrix(size_t m, size_t n) {
    Matrix<T> A(m, n);
    for (size_t i = 0; i != m; ++i) {
        for (size_t j = 0; j != n; ++j) {
            A[i][j] = i + j;
        }
    }
    return A;
}

template <typename T>
std::ostream& operator << (std::ostream& out, const Matrix<T>& A) {
    for (size_t i = 0; i != A.GetRows(); ++i) {
        for (size_t j = 0; j != A.GetColumns(); ++j) {
            out << A[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}
```

main.cpp
```cpp
#include "matrix.h"
#include <iostream>

int main() {
    size_t m, n;
    std::cin >> m >> n;
    Matrix<int> A(m, n);
    // ...
    A = FillMatrix<int>(m, n);
    // std::cout << A.GetRows() << ' ' << A.GetColumns() << '\n';
    // A[m - 1][n - 1] = 1;
    std::cout << A << "\n";
    return 0;
}
```
