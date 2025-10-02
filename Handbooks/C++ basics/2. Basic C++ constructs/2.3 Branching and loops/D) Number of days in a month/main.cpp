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