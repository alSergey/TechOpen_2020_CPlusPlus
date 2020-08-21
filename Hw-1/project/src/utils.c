#include <string.h>
#include "utils.h"


size_t custom_strlen(const char* str) {
    int count = 0;

    while (*str != '\0') {
        count++;
        str++;
    }

    return count;
}

int custom_pow(int base, int power) {
    int result = 1;

    for (int i = 0; i < power; i++) {
        result *= base;
    }

    return result;
}
