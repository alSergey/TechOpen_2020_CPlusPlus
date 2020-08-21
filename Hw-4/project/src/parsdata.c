#include "parsdata.h"

static int get_title(FILE* file, char* data_type_array, char* multipart, data_t* data) {
    if (!file || !data_type_array || !multipart || !data) {
        return -1;
    }

    state_t state = LOOKING_FOR_DATA_TYPE;
    data_type_t data_type = ANOTHER_TYPE;

    while (state != TITLE_END && state != STATE_ERROR) {
        char c = fgetc(file);

        if (state == FINDING_COLON) {
            data_type = get_data_type(data_type_array);
        }

        if (state == FINDING_EQUAL) {
            data_type = get_data_type(multipart);

            if (data_type == ANOTHER_TYPE) {
                state = LOOKING_FOR_SEMICOLON;
            } else {
                state = LOOKING_FOR_BOUNDARY_END;
            }
        }

        if (state == FINDING_SLASH) {
            data_type = get_data_type(multipart);

            if (data_type != MULTIPART) {
                data->part_count = 1;
                state = LOOKING_FOR_ST_END;
            }
        }

        if (data_type == CONTENT_TYPE && state == FINDING_COLON) {
            state = LOOKING_FOR_MULTIPART;
        }

        lexem_t lexem = get_lexem(c);

        if (state == LOOKING_FOR_BOUNDARY_END && lexem == SEMICOLON) {
            data_type = ANOTHER_TYPE;
        }

        rule_t rule = get_syntax(state, lexem);

        state = rule.state;

        if ((state == LOOKING_FOR_ST_END || state == WAITING_FOR_SPACE) && data_type != ANOTHER_TYPE) {
            int i = 0;
            if (c == '"') {
                i = 1;
            }
            if (state == WAITING_FOR_SPACE && c == ' ') {
                state = LOOKING_FOR_ST_END;
                i = 1;
            }
            while (c != '\n' && c != '\r') {
                i++;
                c = fgetc(file);
            }
            fseek(file, -i, SEEK_CUR);

            if (realloc_data(data, i, data_type) == -1) {
                return -1;
            }
            char* st = calloc(i + 1, sizeof(char));
            if (!st) {
                return -1;
            }
            fgets(st, i, file);

            if (rule.action) {
                if (rule.action(st, data, data_type) == -1) {
                    return -1;
                }
            }

            free(st);
        }

        if (state == LOOKING_FOR_BOUNDARY_END && data_type == BOUNDARY) {
            int i = 1;
            while (c != '\n' && c != '\r' && c != ';' && c != ' ') {
                i++;
                c = fgetc(file);
            }
            fseek(file, -i, SEEK_CUR);

            if (realloc_data(data, i, data_type) == -1) {
                return -1;
            }
            char* st = calloc(i + 1, sizeof(char));
            if (!st) {
                return -1;
            }
            fgets(st, i, file);
            if (c == ' ') {
                c = fgetc(file);
            }

            if (rule.action) {
                if (rule.action(st, data, data_type) == -1) {
                    return -1;
                }
            }

            free(st);
        }

        if (rule.data_type_action) {
            if (state == LOOKING_FOR_DATA_TYPE || state == FINDING_COLON) {
                if (rule.data_type_action(c, data_type_array) == -1) {
                    return -1;
                }
            } else {
                if (rule.data_type_action(c, multipart) == -1) {
                    return -1;
                }
            }
        }
    }

    return 0;
}

static int get_body(FILE* file, data_t* data) {
    if (!file || !data) {
        return -1;
    }

    if (data->part_count == 1) {
        return 0;
    }

    if (strlen(data->arr_data[3]) == 0 && data->part_count == 0) {
        data->part_count++;
        return 0;
    }

    char st[4096];

    while (!feof(file) && !ferror(file)) {
        memset(st, '\0', 4096);
        fgets(st, 4096, file);

        size_t strl = strlen(st);
        if (strl > 1) {
            st[strl - 1] = '\0';
            strl--;

            if (st[strl - 1] == '\r' || st[strl - 1] == '\n') {
                st[strl - 1] = '\0';
                strl--;
            }
        }

        if (strncmp(st + 2, data->arr_data[3], data->arr_alloc[3]) == 0) {
            data->part_count++;
        }
    }

    return 0;
}

data_t* get_parser_data(char* file_name) {
    if (!file_name) {
        return NULL;
    }

    // Инициализируем переменные
    data_t* data = init_data();
    if (!data) {
        return NULL;
    }

    char *data_type_array = calloc(15, sizeof(*data_type_array));
    if (!data_type_array) {
        free_data(data);
        return NULL;
    }

    char* multipart = calloc(15, sizeof(*multipart));
    if (!multipart) {
        free(data_type_array);
        free_data(data);
        return NULL;
    }

    FILE *file = fopen(file_name, "r");
    if (!file) {
        free(data_type_array);
        free(multipart);
        free_data(data);
        return NULL;
    }

    // Обрабатываем заголовок файла
    if (get_title(file, data_type_array, multipart, data) == -1) {
        fclose(file);
        free(data_type_array);
        free(multipart);
        free_data(data);
        return NULL;
    }

    // Убираем лишние кавычки, добавляем -- к boundary
    if (check_data_quotes(data) == -1) {
        fclose(file);
        free(data_type_array);
        free(multipart);
        free_data(data);
        return NULL;
    }

    // Обрабатываем тело файла
    if (get_body(file, data) == -1) {
        fclose(file);
        free(data_type_array);
        free(multipart);
        free_data(data);
        return NULL;
    }

    // Очищаем данные
    free(data_type_array);
    free(multipart);
    fclose(file);

    return data;
}
