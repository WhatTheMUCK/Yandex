# Количество дней в месяце

## Ограничения

| Параметр             | Значение            |
|----------------------|---------------------|
| Ограничение времени  | 1 секунда           |
| Ограничение памяти   | 64.0 Мб             |
| Ввод                 | стандартный ввод или `input.txt` |
| Вывод                | стандартный вывод или `output.txt` |

---

## Условие задачи

Напишите программу, выводящую количество дней в месяце по заданному номеру месяца и году.

### Формат ввода

На вход программе подается два целых положительных числа: номер месяца (от 1 до 12) и четырёхзначный год.

### Формат вывода

Необходимо вывести одно число — количество дней в заданном месяце.

---

## Примеры

### Пример 1

Ввод:
```
1 2001
```

Вывод:
```
31
```

### Пример 2

Ввод:
```
2 2001
```

Вывод:
```
28
```

---

## Примечание

Рекомендуется сначала решить задачу **«Високосный год»** и использовать её решение для вывода количества дней в феврале.
## Решение

main.cpp
```cpp
#include <iostream>

enum class MonthName {
    January, // Индексация с 0
    February,
    March,
    April,
    May,
    June,
    July,
    August,
    September,
    October,
    November,
    December
};

struct Year {
    Year() : year_(0) {}
    Year(int year) : year_(year) {}

    bool Leap() {
        if (year_ % 400 == 0 || (year_ % 100 != 0 && year_ % 4 == 0)) {
            return true;
        } 
        return false;
    }

    int year_;
};

struct MonthInfo {
    MonthInfo(int month, int year)
    : month_(month) {
        Year year_(year);
        if (year_.Leap() == true) {
            daysInMonth_[static_cast<int>(MonthName::February)] = 29;
        }
    }

    int getAmountOfDays() const {
        return daysInMonth_[month_ - 1];
    }

    int month_;
    Year year_;
private:
    int daysInMonth_[12] = {
        31, // January
        28, // February (невисокосный год)
        31, // March
        30, // April
        31, // May
        30, // June
        31, // July
        31, // August
        30, // September
        31, // October
        30, // November
        31  // December
    };
};

int main() {
    int month, year;
    std::cin >> month >> year;
    MonthInfo monthInfo(month, year);
    std::cout << monthInfo.getAmountOfDays() << '\n';
    return 0;
}
```
