# AdvancedVector

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Реализуйте класс `AdvancedVector`. Продвинутый вектор отличается от обычного тем, что позволяет обращаться по **отрицательным индексам** к элементам вектора в обратном порядке (прямо как в Python). Например:
- `vec[-1]` возвращает последний элемент,
- `vec[-2]` возвращает предпоследний и так далее.

### Требования к классу

Класс `AdvancedVector` должен хранить элементы шаблонного типа `T` и поддерживать следующий функционал:

- Класс должен называться `AdvancedVector`.
- У класса должен быть шаблонный параметр `T` — тип элементов.
- У класса должен быть **конструктор по умолчанию**.
- У класса должен быть **конструктор копирования** (может быть сгенерирован компилятором).
- У класса должен быть **шаблонный конструктор**, принимающий два итератора и заполняющий вектор из заданного диапазона.
- У класса должен быть **оператор присваивания** (может быть сгенерирован компилятором).
- У класса должны быть **операторы сравнения** `==` и `!=`.
- У класса должны быть **константные функции** `empty()` и `size()`.
- У класса должны быть функции `pop_back()` и `push_back(const T&)`.
- У класса должны быть **константная и неконстантная версии оператора `[]`**.

### Поведение оператора `[]`

- При **положительном индексе** `i`:  
  - если `i < size()`, вернуть `data[i]`;  
  - иначе — бросить исключение `std::out_of_range`.

- При **отрицательном индексе** `i`:  
  - если `abs(i) <= size()`, вернуть `data[size() + i]` (например, `-1` → `size() - 1`);  
  - иначе — бросить исключение `std::out_of_range`.

> **Гарантия:** передаваемый в `operator[]` индекс всегда лежит в диапазоне `[−10⁹; 10⁹]`.

### Примечание

- Сдайте **только код класса `AdvancedVector`**, без функции `main`.
- Подключите все необходимые заголовочные файлы в вашем решении.
## Решение

main.cpp
```cpp
#include <iostream>
#include <vector>

template <typename T>
class AdvancedVector : public std::vector<T> {
public:
    // Наследуем конструкторы от std::vector
    using std::vector<T>::vector;

    T & operator[](int index){
        int n = static_cast<int>(this->size());
        if (index >= n || -index > n) {
            throw std::out_of_range("index out of range");
        }

        if (0 <= index && index < n) {
            return this->at(index);
        }

        return this->at(n + index);
    }

    const T & operator[](int index) const {
        int n = static_cast<int>(this->size());
        if (index >= n || -index > n) {
            throw std::out_of_range("index out of range");
        }

        if (0 <= index && index < n) {
            return this->at(index);
        }

        return this->at(n + index);
    }
};

int main() {
    AdvancedVector<char> tmp({'a', 'b', 'c'});
    for (int i = 1; i <= 3; ++i) {
        std::cout << tmp[-i] << ' ';
    }
    std::cout << '\n';
    int n;
    std::cin >> n;
    AdvancedVector<double> vec(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }
    // std::cout << vec[-1] << '\n';
    for (int i = 1; i <= n; ++i) {
        std::cout << vec[-i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
```
