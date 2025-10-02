# Снова жизнь объекта

**Ограничение времени**  
1 с  

**Ограничение памяти**  
64.0 Мб  

**Ввод**  
стандартный ввод или `input.txt`  

**Вывод**  
стандартный вывод или `output.txt`

Вам дан класс `A` и функция `main()`:

```cpp
#include <iostream>
#include <memory>

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
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

#include "your_code.h"

int main() {
    std::unique_ptr<A> ptr(new B);
    ptr->foo();
}
```

Напишите такой код класса `B`, чтобы функция `main()` вывела бы сообщения:

```text
Constructor(int): 42
Constructor(int): 17
A::foo()
Destructor
Destructor
```

**Примечание**

Не пытайтесь вывести нужный текст с помощью непосредственной печати: мы при проверке всё равно заменяем отладочные сообщения в классе на свои.
## Решение

main.cpp
```cpp
#include <iostream>
#include <memory>

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
    virtual void foo() const {
        std::cout << "A::foo()\n";
    }
};

// My code
class B : public A {
public:
    B() : A(42), temp(17) {}

private:
    A temp;
};
//

int main() {
    std::unique_ptr<A> ptr(new B);
    ptr->foo();
}
```
