#include <iostream>
#include <chrono>

class TimerGuard {
public:
    TimerGuard(const std::string & message = "", std::ostream & out = std::cout) 
    : message_(message) 
    , out_(out)
    , start_(std::chrono::high_resolution_clock::now()) 
    {}

    ~TimerGuard() {
        std::chrono::duration<double> diff = std::chrono::high_resolution_clock::now() - start_;
        out_ << message_ << ' ' << diff.count() << '\n';
    }

private:
    const std::string message_;
    std::ostream & out_;
    const std::chrono::high_resolution_clock::time_point start_;
};

#include <unistd.h>

void SomeFunction(int n) {
    sleep(n);
    return;
}

int main() {
    {
        TimerGuard timer("1): ", std::cout);
        SomeFunction(5);
    }
    {
        TimerGuard timer("2): ", std::cout);
        SomeFunction(10);
    }
}
