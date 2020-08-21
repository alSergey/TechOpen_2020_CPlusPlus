#include "parsdata.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }
    char *file_name = argv[1];
    if (!file_name) {
        return -1;
    }

    data_t* data = get_parser_data(file_name);
    if (!data) {
        return -1;
    }

    if (parser_print(data) == -1) {
        free_data(data);
        return -1;
    }

    free_data(data);

    return 0;
}
