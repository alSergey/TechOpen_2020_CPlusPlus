#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "utils_prime.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3


int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    const char* data = argv[2];
    switch (atoi(argv[1])) {
        case TST_FOO_FIX: {
            printf("%zu\n", custom_strlen(data));
            break;
        }

        case TST_FOO_IMPL: {
            if (argc != 4) {
                return ERR_ARGS_COUNT;
            }

            printf("%i\n", custom_pow(atoi(data), atoi(argv[3])));
            break;
        }

        case TST_MOD_IMPL: {
            printf("%i\n", is_prime(atoi(data)));
            break;
        }

        default: {
            return ERR_WRONG_FLG;
        }
    }

    return 0;
}
