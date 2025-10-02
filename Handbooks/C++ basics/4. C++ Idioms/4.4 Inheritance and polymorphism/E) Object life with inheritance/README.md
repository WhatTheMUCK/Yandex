# Жизнь объекта с наследованием

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Вам дан класс `A`, который в своих конструкторах и деструкторе печатает соответствующие сообщения, а также функция `main`:

```cpp
#include <iostream>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const = 0;
};

#include "your_code.h"

int main() {
    B b;
    const A& a = b;
    a.foo();
}
```

Вам требуется написать код класса `B`, чтобы функция `main`, работающая с этим классом, вывела следующие сообщения:

```text
Constructor(int): 42
Destructor
```

### Примечание
- **Не пытайтесь** вывести нужный текст с помощью непосредственной печати (например, `std::cout << "Constructor(int): 42\n";`).
- При проверке отладочные сообщения в классе `A` будут заменены на другие — ваша реализация должна **корректно вызывать конструктор и деструктор базового класса**, а не эмулировать вывод.
## Решение

main.cpp
```cpp
#include <iostream>

class A {
public:
    A(int x) {
        std::cout << "Constructor(int): " << x << "\n";
    }
    A(const A&) {
        std::cout << "Copy constructor\n";
    }
    virtual ~A() {
        std::cout << "Destructor\n";
    }
    virtual void foo() const = 0;
};

// Мой код

class B : public A {
public:
    B() : A(42) {}
    void foo() const override {}
};

//

int main() {
    B b;
    const A& a = b;
    a.foo();
}
```
