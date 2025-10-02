#include "logger.h"

int main() {
    Logger first;
    Logger second(first);
    return 0;
}