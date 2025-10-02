# TimerGuard

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вася хочет замерять время работы разных частей своей программы. Сейчас он делает это средствами стандартной библиотеки так:

```cpp
#include <iostream>
#include <chrono>

#include "some_long_stuff.h"

void SomeFunc() {
    auto start1 = std::chrono::high_resolution_clock::now();
    FirstLongFunction();
    std::chrono::duration<double> diff1 = std::chrono::high_resolution_clock::now() - start1;
    std::cout << "FirstLongFunction elapsed: " << diff1.count() << "\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    SecondLongFunction();
    std::chrono::duration<double> diff2 = std::chrono::high_resolution_clock::now() - start2;
    std::cout << "SecondLongFunction elapsed: " << diff2.count() << "\n";

    auto start3 = std::chrono::high_resolution_clock::now();
    ThirdLongFunction();
    std::chrono::duration<double> diff3 = std::chrono::high_resolution_clock::now() - start3;
    std::cout << "ThirdLongFunction elapsed: " << diff3.count() << "\n";
}

int main() {
    SomeFunc();
    return 0;
}
```

Но ему очень неудобно каждый раз прописывать начало замера и конец. Помогите ему сделать это удобнее.

---

## Задача

Напишите обёртку `TimerGuard`. Это класс, который:

- Создаётся перед началом вычислений,
- При выходе из своего scope (уничтожении объекта) **автоматически** выводит в заданный поток время своей жизни.

С его помощью Вася сможет писать так:

```cpp
#include <iostream>
#include <chrono>

#include "some_long_stuff.h"

void SomeFunc() {
    {
        TimerGuard timer("FirstLongFunction elapsed: ", std::cout);
        FirstLongFunction();
    }
    {
        TimerGuard timer("SecondLongFunction elapsed: ", std::cout);
        SecondLongFunction();
    }
    {
        TimerGuard timer("ThirdLongFunction elapsed: ", std::cout);
        ThirdLongFunction();
    }
}
```

---

### Требования к классу `TimerGuard`:

- Конструктор принимает два аргумента:
  - `const std::string& message` — префикс сообщения (например, `"Function X elapsed: "`)
  - `std::ostream& out` — поток, в который нужно вывести результат (например, `std::cout`)
- В конструкторе запоминается текущее время.
- В деструкторе вычисляется разность между текущим временем и временем создания, и в указанный поток выводится строка вида:  
  `"<message><время_в_секундах>\n"`
- Время должно измеряться с помощью `std::chrono::high_resolution_clock`.
- Время выводится как число типа `double` (в секундах), как в примере выше.

---

**Примечание**  
Сдайте только код класса `TimerGuard` (включая необходимые `#include`). Функции `main` в решении быть не должно.