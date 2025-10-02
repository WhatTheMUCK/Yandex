#include "logger.h"

int main() {
    Logger first;
    Logger second;
    first = second;
    first = std::move(second);
    return 0;
}