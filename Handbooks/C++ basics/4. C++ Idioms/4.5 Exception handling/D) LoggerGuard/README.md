# LoggerGuard

## Ограничения
- **Время:** 1 с  
- **Память:** 64.0 Мб  
- **Ввод:** стандартный ввод или `input.txt`  
- **Вывод:** стандартный вывод или `output.txt`

## Условие задачи

Вася хочет выводить сообщение при завершении функции — независимо от того, как именно она завершилась:
- через `return`,
- через исключение,
- или просто дошёл до конца.

В текущем подходе приходится дублировать код вывода в каждом `return` и в `catch`-блоке, что делает программу громоздкой и подверженной ошибкам.

### Цель

Реализовать класс `LoggerGuard`, который автоматически выводит заданное сообщение **при выходе из области видимости** (например, при выходе из функции), используя механизм RAII (деструктор вызывается всегда — даже при исключениях).

### Требуемый интерфейс

Класс должен иметь следующий конструктор:

```cpp
LoggerGuard(const std::string& message, std::ostream& out = std::cout);
```

- `message` — текст сообщения, которое нужно вывести.
- `out` — поток вывода (по умолчанию `std::cout`).
- **Важно:** даже если `message` не содержит `\n`, вы **обязаны** вывести его с завершающим переводом строки.

### Пример использования

Без `LoggerGuard` (плохо):

```cpp
#include <iostream>

int Function() {
    int value = 1;
    try {
        value = SomeFunction();
        if (value == 0) {
            std::cout << "Function completed\n";
            return value;
        }

        value = SomeOtherFunction();
        if (value == 0) {
            std::cout << "Function completed\n";
            return value;
        }

        value = FinalFunction();  // might throw an exception
    } catch (...) {
        std::cout << "Function completed\n";
        throw;
    }

    std::cout << "Function completed\n";
    return value;
}
```

С `LoggerGuard` (хорошо):

```cpp
#include <iostream>

int Function() {
    LoggerGuard logger("Function completed");

    int value = 1;
    try {
        value = SomeFunction();
        if (value == 0) {
            return value;
        }

        value = SomeOtherFunction();
        if (value == 0) {
            return value;
        }

        value = FinalFunction();  // might throw an exception
    } catch (...) {
        throw;
    }

    return value;
}
```

### Требования
- Реализуйте **только класс `LoggerGuard`**.
- Подключите необходимые заголовочные файлы (`<string>`, `<ostream>` и т.д.).
- Не добавляйте `main` и не изменяйте поведение других функций.
- Убедитесь, что сообщение выводится **ровно один раз** при выходе из функции — даже если выброшено исключение.
## Решение

main.cpp
```cpp
#include <iostream>

class LoggerGuard {
public:
    LoggerGuard(const std::string& message, std::ostream & out = std::cout)
    : message_(message)
    , out_(out)
    {}

    ~LoggerGuard() {
        out_ << message_ << '\n';
    }
private:
    const std::string message_;
    std::ostream & out_;
};

int first = 0, second = 0, third = 0;

int SomeFunction() {
    if (first == 42) {
        throw std::out_of_range("42!!!");
    }
    return first;
}

int SomeOtherFunction() {
    if (second == 42) {
        throw std::out_of_range("42!!!");
    }
    return second;
}

int FinalFunction() {
    if (third == 42) {
        throw std::out_of_range("42!!!");
    }
    return third;
}

int Function() {
    LoggerGuard logger("Function completed");

    int value = 1;
    try {
        value = SomeFunction();
        if (value == 0) {
            return value;
        }

        value = SomeOtherFunction();
        if (value == 0) {
            return value;
        }

        value = FinalFunction();  // might throw an exception
    } catch (...) {
        throw;  // throws the exception further.
    }

    return value;
}

int main() {
    std::cin >> first >> second >> third;
    try {
        int answer = Function();
        std::cout << "answer = " << answer << '\n';
    } catch (...) {
        std::cout << "Штош\n";
    }
    return 0;
}
```
