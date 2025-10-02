# Адреса

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Алексею поручили написать программу, обрабатывающую почтовые адреса.

Дана структура `Address` и несколько работающих с ней функций:

```cpp
#pragma once

#include <string>

struct Address {
    std::string Country;
    std::string City;
    std::string Street;
    std::string House;
};

void Parse(const std::string& line, Address* const address);
void Unify(Address* const address);
std::string Format(const Address& address);
```

- `Parse` принимает строку и пытается выделить из неё компоненты адреса.
- `Unify` приводит компоненты адреса к каноническому виду (например, «пр-д Кочновский» → «Кочновский проезд»).
- `Format` возвращает текстовое представление адреса.

Функции `Parse` и `Unify` следуют стилю Google C++: они принимают изменяемый объект через **указатель**, предполагая, что объект уже создан.

В случае ошибок эти функции **могут генерировать исключения**.

### Проблемный код

Алексей написал следующую программу:

```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    Address* address;
    while (getline(std::cin, line)) {
        Parse(line, address);
        Unify(address);
        std::cout << Format(*address) << "\n";
    }
}
```

Предполагалось, что эта программа будет читать поступающие на вход строки, извлекать из них адреса и печатать их обработанные текстовые представления. В случае исключений при обработке строки программа должна напечатать просто “exception” (с переводом строки) и перейти к обработке следующих строк.

### Примечание

Вам нужно исправить ошибки в коде и сдать его в систему. Код структуры Address и функций переписывать не надо: просто подключите в своей программе заголовочный файл address.h. Утечек памяти в вашей программе быть не должно.
## Решение

address.h
```cpp
#pragma once

#include <string>

struct Address {
    std::string Country;
    std::string City;
    std::string Street;
    std::string House;
};

void Parse(const std::string& line, Address* const address);
void Unify(Address* const address);
std::string Format(const Address& address);


```

main.cpp
```cpp
#include "address.h"
#include <iostream>
#include <string>

int main() {
    std::string line;
    while (getline(std::cin, line)) {
        Address* address = new Address;
        try {
            Parse(line, address);
            Unify(address);
            std::cout << Format(*address) << "\n";
        } catch(...) {
            std::cout << "exception\n";
        }
        delete address;
    }
}
```
