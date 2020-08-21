#include "test.h"

int main(void) {
    int err = test_write_to_file();

    if (err == -1) {
        printf("Error test\n");
    }
}
