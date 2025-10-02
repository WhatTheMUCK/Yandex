#include "logger.h"

int main() {
    Logger first;
    Logger * second = new Logger();
    Logger third;
    delete second;
    return 0;
}