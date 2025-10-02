#include "logger.h"

int main() {
    Logger first;
    Logger second(std::move(first));
    return 0;
}