# Многочлены

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Многочлен от одной переменной — алгебраическое выражение, состоящее из суммы нескольких произведений числовых коэффициентов на переменную в натуральной степени. Пример: `x² + 2x + 1`. Слагаемыми в многочлене называют **одночлены**.

Как и в задаче о математическом векторе, числами здесь могут являться любые объекты со стандартным набором базовых математических операций (сложение, вычитание, умножение, деление), например: дробные, вещественные или комплексные числа, а также математические матрицы и другие алгебраические объекты.

---

## Задача

Реализуйте шаблонный класс `Polynomial` (многочлен от одной переменной) на основе контейнера `std::vector`. Тип коэффициентов многочлена передавайте в качестве параметра шаблона. Хранение коэффициентов должно быть **плотным** (то есть должны храниться все коэффициенты, в том числе и промежуточные нулевые).

---

## Требования к классу

### 1. Конструкторы

Реализуйте следующие конструкторы:

- Создаёт многочлен по заданному вектору коэффициентов (коэффициенты задаются **по возрастанию степени**).
- Создаёт многочлен по заданному коэффициенту (многочлен нулевой степени), который равен значению по умолчанию параметра шаблона.
- Создаёт многочлен по заданным итераторам на начало и следующий за концом последовательности коэффициентов (аналогично, по возрастанию степени).

---

### 2. Операторы сравнения

Перегрузите операторы `==` и `!=`.  
✅ Ваш код должен быть очень простым.  
✅ Операторы должны работать и в том случае, когда один из аргументов — скалярная величина.

---

### 3. Арифметические операторы

Перегрузите операторы `+`, `-`, `*`, а также соответствующие составные операторы `+=`, `-=`, `*=`.  
✅ Учтите, что должны быть определены и такие арифметические операции, в которых один из аргументов — скалярная величина.

---

### 4. Оператор индексации и степень

- Перегрузите оператор `[]` для получения коэффициента многочлена перед заданной степенью переменной.  
  ✅ Достаточно **константной версии**.  
  ✅ Оператор должен работать для **любых степеней** (включая больше текущей максимальной — возвращать 0).  
- Напишите метод `Degree()` для вычисления степени многочлена.  
  ✅ Считайте, что у **нулевого многочлена** степень равна `-1`.

---

### 5. Вычисление значения

Перегрузите оператор `()` для вычисления значения многочлена в точке.  
✅ В качестве аргумента принимает значение того типа, от которого создан многочлен.  
✅ Постарайтесь написать **эффективный код** (например, схема Горнера).

---

### 6. Вывод

Перегрузите оператор `<<` для печати многочлена в поток вывода.  
✅ Для простоты выводите коэффициенты **через пробел от старшей степени к младшей**.

---

### 7. Итераторы

Предусмотрите методы `begin()` и `end()` для доступа к **константным итераторам**, позволяющим перебрать коэффициенты многочлена.  
✅ Это могут быть просто итераторы вектора.  
✅ **Ведущие нули** коэффициентами не считаются.  
✅ Итерация должна происходить **по возрастанию степени**.

---

## Примечание

- В вашем решении должен быть **только код класса** и **не должно быть функции `main`**.
- При проверке наша программа будет использовать ваш класс `Polynomial`. Она сама прочитает из входного потока коэффициенты многочленов и выведет их сумму, разность, произведение и т. д.
- ⚠️ Если какой-то из операторов реализован, но его вызов **не компилируется**, вы получите **неправильный ответ**, а не ошибку компиляции — тестирующая система доопределяет неработающие операторы.
- Вы можете считать, что шаблонный параметр — это числовой тип, для которого реализованы:
  - все арифметические операции,
  - операции сравнения,
  - вывод в поток,
  - конструирование от `int`.
- ❗ Наличие **неявного конструктора** или **оператора приведения типа не гарантируется** — вызывайте конструктор **явно**.
## Решение

main.cpp
```cpp
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
```
