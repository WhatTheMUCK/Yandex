# Жизнь объекта - 6

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

В предыдущей задаче вам был дан готовый класс `Logger`, который в своих конструкторах, операторах присваивания и деструкторе печатает соответствующие сообщения.

Вам требуется написать программу, которая работает с этим классом и выводит по заданному `n` следующий текст:

```text
Logger(): 1
Logger(): 2
...
Logger(): n
~Logger(): 1
~Logger(): 2
...
~Logger(): n
```

---

### Формат ввода

На вход поступает натуральное число `n`, не превосходящее `1000`.

### Формат вывода

Ваша программа должна каким-либо образом создать `n` объектов типа `Logger`, а затем уничтожить их в **прямом порядке**. Никаких посторонних сообщений программа печатать не должна.

---

**Примечание**  
- Не вставляйте код класса в решение. Используйте вместо этого директиву `#include "logger.h"` в начале программы.  
- Не пытайтесь вывести нужный текст с помощью непосредственной печати: мы при проверке всё равно заменяем отладочные сообщения в классе на свои.
## Решение

logger.h
```cpp
#include <iostream>

class Logger {
private:
    static int counter;
    const int id;

public:
    Logger(): id(++counter) {
        std::cout << "Logger(): " << id << "\n";
    }

    Logger(const Logger& other): id(++counter) {
        std::cout << "Logger(const Logger&): " << id << " " << other.id << "\n";
    }

    Logger(Logger&& other): id(++counter) {
        std::cout << "Logger(Logger&&): " << id << " " << other.id << "\n";
    }

    Logger& operator = (const Logger& other) {
        std::cout << "Logger& operator = (const Logger&): " << id << " " << other.id << "\n";
        return *this;
    }

    Logger& operator = (Logger&& other) {
        std::cout << "Logger& operator = (Logger&&): " << id << " " << other.id << "\n";
        return *this;
    }

    ~Logger() {
        std::cout << "~Logger(): " << id << "\n";
    }
};

int Logger::counter = 0;
```

main.cpp
```cpp
#include "logger.h"
#include <deque>

int main() {
    int n;
    std::cin >> n;
    std::deque<Logger> container(n);
    for (int i = 0; i < n; ++i) {
        container.pop_front();
    }
    return 0;
}
```
