# Зоопарк

**Ограничение времени**  
1 с  

**Ограничение памяти**  
64.0 Мб  

**Ввод**  
стандартный ввод или `input.txt`  

**Вывод**  
стандартный вывод или `output.txt`

Вы работаете с иерархией классов, описывающих животных:

```cpp
#pragma once

#include <string>

class Animal {
public:
    virtual std::string Voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};

class Tiger: public Animal {
    std::string Voice() const override {
        return "Rrrr";
    }
};

class Wolf: public Animal {
    std::string Voice() const override {
        return "Wooo";
    }
};

class Fox: public Animal {
    std::string Voice() const override {
        return "Tyaf";
    }
};
```

Вам нужно определить тип `Zoo`, представляющий из себя набор различных животных, и написать две функции: `Zoo CreateZoo()` и `void Process(const Zoo& zoo)`.

Функция `CreateZoo` должна читать слова из стандартного ввода. Если на вход поступают слова `Tiger`, `Wolf` или `Fox`, она должна поместить соответствующего зверя в зоопарк. Если на вход поступает другое слово, она должна прекратить чтение и сгенерировать исключение `std::runtime_error`.

Функция `Process` должна перебрать всех зверей в зоопарке в порядке создания и напечатать для каждого из них результат работы виртуальной функции `Voice`.

Ваш коллега написал вот такой код, но он почему-то не работает:

```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

#include "animals.h"

using Zoo = std::vector<Animal>;

Zoo CreateZoo() {
    Zoo zoo;
    std::string word;
    while (std::cin >> word) {
        if (word == "Tiger") {
            Tiger t;
            zoo.push_back(t);
        } else if (word == "Wolf") {
            Wolf w;
            zoo.push_back(w);
        } else if (word == "Fox") {
            Fox f;
            zoo.push_back(f);
        } else
            throw std::runtime_error("Unknown animal!");
    }
    return zoo;
}

void Process(const Zoo& zoo) {
    for (const auto& animal : zoo) {
        std::cout << animal.Voice() << "\n";
    }
}
```

Исправьте его и сдайте в систему.

**Примечание**

Код классов из файла `animals.h` переписывать не надо, просто подключите заголовочный файл `animals.h`. Обратите внимание, что в нашей версии файла `animals.h` голоса зверей могут отличаться от того, что приведено в примере. Разумеется, в вашей программе не должно быть утечек памяти. Экземпляр каждого зверя надо создавать ровно один раз (если вам на входе даны два волка, то надо создать ровно два объекта типа `Wolf`, не больше и не меньше).
## Решение

animals.h
```cpp
#pragma once

#include <string>

class Animal {
public:
    virtual std::string Voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};

class Tiger: public Animal {
    std::string Voice() const override {
        return "Rrrr";
    }
};

class Wolf: public Animal {
    std::string Voice() const override {
        return "Wooo";
    }
};

class Fox: public Animal {
    std::string Voice() const override {
        return "Tyaf";
    }
};
```

main.cpp
```cpp
#include <iostream>
#include <stdexcept>
#include <vector>

#include "animals.h"
#include <memory>

using Zoo = std::vector<std::unique_ptr<Animal>>;

Zoo CreateZoo() {
    Zoo zoo;
    std::string word;
    while (std::cin >> word) {
        if (word == "Tiger") {
            zoo.push_back(std::make_unique<Tiger>());
        } else if (word == "Wolf") {
            zoo.push_back(std::make_unique<Wolf>());
        } else if (word == "Fox") {
            zoo.push_back(std::make_unique<Fox>());
        } else
            throw std::runtime_error("Unknown animal!");
    }
    return zoo;
}

void Process(const Zoo& zoo) {
    for (const auto& animal : zoo) {
        std::cout << animal->Voice() << "\n";
    }
}

int main() {
    Zoo zoo = CreateZoo();
    Process(zoo);
    return 0;
}
```
