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