#include <iostream>
#include <tuple>


class Date {
private:
    int days_;

    static bool IsLeap(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int DaysInMonth(int month, int year) {
        static const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && IsLeap(year)) return 29;
        return days[month - 1];
    }

    int ToDays(int day, int month, int year) const {
        int days = 0;
        for (int y = 1970; y < year; ++y) {
            days += IsLeap(y) ? 366 : 365;
        }
        for (int m = 1; m < month; ++m) {
            days += DaysInMonth(m, year);
        }
        days += day - 1;
        return days;
    }

    std::tuple<int, int, int> FromDays() const {
        int days = days_;
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

        return std::tuple(days + 1, m, y);
    }

public:
    Date() : Date(1, 1, 1970) {}
    Date(int days) : days_(days) {}
    Date(int day, int month, int year) {
        if (day <= 0 || month <= 0 || month > 12 || year < 1970 || year > 2099 ||
            day > DaysInMonth(month, year)) {
            *this = Date(1, 1, 1970);
            return;
        }
        days_ = ToDays(day, month, year);
    }

    int GetDay() const { return std::get<0>(FromDays()); }
    int GetMonth() const { return std::get<1>(FromDays()); }
    int GetYear() const { return std::get<2>(FromDays()); }

    Date operator+(int days) const {
        return Date(days_ + days);
    }

    Date operator-(int days) const {
        return Date(days_ - days);
    }

    int operator-(const Date& other) const {
        return days_ - other.days_;
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