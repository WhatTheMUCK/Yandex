# Дата

**Ограничение времени**  
 1 с  
**Ограничение памяти**  
 64.0 Мб  
**Ввод**  
 стандартный ввод или input.txt  
**Вывод**  
 стандартный вывод или output.txt  

Вам надо написать класс `Date` для хранения даты григорианского календаря. Используйте три переменных типа `int` для хранения дня, месяца и года. В вашем классе должен быть следующий публичный интерфейс:

- Конструктор, принимающий на вход три числа: день, месяц и год. В случае некорректной даты должна создаваться дата **1 января 1970 года**.
- Константные функции `GetDay`, `GetMonth` и `GetYear`.
- Бинарные операторы `+` и `-`, где вторым аргументом является целое число — количество дней. Эти операторы должны вернуть новую дату, отстоящую от заданной на указанное число дней.
- Бинарный оператор `-`, вычисляющий разность между двумя датами и возвращающий `int` — количество дней.

Считайте, что все обрабатываемые даты будут лежать в пределах от **1 января 1970 года** до **31 декабря 2099 года**.

---

**Примечание**  
Сдайте в систему только код класса `Date` без функции `main`.
## Решение

main.cpp
```cpp
#include <iostream>

class Date {
private:
    int day_, month_, year_;

    static bool IsLeap(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int DaysInMonth(int month, int year) {
        static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && IsLeap(year)) return 29;
        return days[month - 1];
    }

    void Normalize() {
        while (month_ < 1) {
            year_--;
            month_ += 12;
        }
        while (month_ > 12) {
            year_++;
            month_ -= 12;
        }

        while (day_ > DaysInMonth(month_, year_)) {
            day_ -= DaysInMonth(month_, year_);
            month_++;
            if (month_ > 12) {
                month_ = 1;
                year_++;
            }
        }

        while (day_ <= 0) {
            month_--;
            if (month_ < 1) {
                month_ = 12;
                year_--;
            }
            day_ += DaysInMonth(month_, year_);
        }

        if (year_ < 1970 || year_ > 2099) {
            *this = Date(1, 1, 1970);
        }
    }

    int ToDays() const {
        int days = 0;
        for (int y = 1970; y < year_; ++y) {
            days += IsLeap(y) ? 366 : 365;
        }
        for (int m = 1; m < month_; ++m) {
            days += DaysInMonth(m, year_);
        }
        days += day_ - 1;
        return days;
    }

    static Date FromDays(int days) {
        int y = 1970;
        while (days >= (IsLeap(y) ? 366 : 365)) {
            days -= IsLeap(y) ? 366 : 365;
            y++;
        }

        int m = 1;
        while (days >= DaysInMonth(m, y)) {
            days -= DaysInMonth(m, y);
            m++;
        }

        return Date(days + 1, m, y);
    }

public:
    Date() : Date(1, 1, 1970) {}

    Date(int day, int month, int year) : day_(day), month_(month), year_(year) {
        if (day <= 0 || month <= 0 || month > 12 || year < 1970 || year > 2099 ||
            day > DaysInMonth(month, year)) {
            *this = Date(1, 1, 1970);
            return;
        }
        Normalize(); // на всякий случай, хотя входные данные корректны
    }

    int GetDay() const { return day_; }
    int GetMonth() const { return month_; }
    int GetYear() const { return year_; }

    Date operator+(int days) const {
        return FromDays(ToDays() + days);
    }

    Date operator-(int days) const {
        return FromDays(ToDays() - days);
    }

    int operator-(const Date& other) const {
        return ToDays() - other.ToDays();
    }
};

std::ostream& operator<<(std::ostream& os, const Date& d) {
    return os << d.GetDay() << '-' << d.GetMonth() << '-' << d.GetYear();
}

int main() {
    int day, month, year;
    std::cin >> day >> month >> year;
    Date day1(day, month, year);
    std::cout << "day1: " << day1 << '\n';
    std::cin >> day >> month >> year;
    Date day2(day, month, year);
    std::cout << "day2: " << day2 << "\n\n";
    std::cout << day1 - day2 << "\n\n";

    std::cin >> day >> month >> year;
    Date curDay(day, month, year);
    std::cout << curDay << '\n';
    int shift;
    while (std::cin >> shift) {
        std::cout << (curDay = curDay + shift) << '\n'; 
    }
    return 0;
}
```
