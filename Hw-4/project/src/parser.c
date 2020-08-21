#include "parser.h"

// data_type_t
data_type_t get_data_type(char* st) {
    char* arr[6] = {"from:", "to:", "date:", "boundary=", "content-type:", "multipart/"};
    for (int i = 0; i < 6; i++) {
        if (strncasecmp(st, arr[i], strlen(arr[i])) == 0) {
            return i;
        }
    }

    return ANOTHER_TYPE;
}

// lexem_t
lexem_t get_lexem(char c) {
    switch (c) {
        case ' ': case '\t': {
            return SPACE;
        }

        case ':': {
            return COLON;
        }

        case '/': {
            return SLASH;
        }

        case ';': {
            return SEMICOLON;
        }

        case '=': {
            return EQUAL;
        }

        case '\n': {
            return ST_END_CHARACTER_N;
        }

        case '\r': {
            return ST_END_CHARACTER_R;
        }

        default: {
            return CHARACTER;
        }
    }
}

// action_t
int copy_to_data(char* st, data_t* data, data_type_t data_type) {
    if (!data) {
        return -1;
    }

    switch (data_type) {
        case FROM: {
            strncpy(data->arr_data[0] + strlen(data->arr_data[0]), st, strlen(st));
            break;
        }

        case TO: {
            strncpy(data->arr_data[1] + strlen(data->arr_data[1]), st, strlen(st));
            break;
        }

        case DATE: {
            strncpy(data->arr_data[2] + strlen(data->arr_data[2]), st, strlen(st));
            break;
        }

        case BOUNDARY: {
            strncpy(data->arr_data[3] + strlen(data->arr_data[3]), st, strlen(st));
        }

        default: {
            break;
        }
    }

    return 0;
}

// data_type_action_t
int add_data_type(char c, char* data_type_array) {
    if (!data_type_array) {
        return -1;
    }

    size_t strl = strlen(data_type_array);
    if (strl < 14) {
        if (c != ' ' && c != '\n' && c != '\r') {
            data_type_array[strl] = c;
        }
    }

    return 0;
}

int add_clear_data_type(char c, char* data_type_array) {
    if (!data_type_array) {
        return -1;
    }

    memset(data_type_array, '\0', strlen(data_type_array));

    if (c != ' ' && c != '\n' && c != '\r') {
        data_type_array[0] = c;
    }

    return 0;
}

// rule_t
rule_t syntax[STATE_COUNT][LEXEM_COUNT] = {
    /* LOOKING_FOR_DATA_TYPE */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_DATA_TYPE, NULL, add_data_type},       {LOOKING_FOR_ST_END, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {FINDING_COLON, NULL, add_data_type},                {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {LOOKING_FOR_DATA_TYPE, NULL, NULL},                 {LOOKING_FOR_DATA_TYPE, NULL, NULL}},

    /* FINDING_COLON */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_ST_END, copy_to_data, NULL},           {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL}},

    /* LOOKING_FOR_MULTIPART */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_MULTIPART, NULL, add_data_type},       {LOOKING_FOR_MULTIPART, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {FINDING_SLASH, NULL, add_data_type},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL}},

    /* FINDING_SLASH */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_SEMICOLON, NULL, add_clear_data_type}, {LOOKING_FOR_SEMICOLON, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL}},


    /* LOOKING_FOR_SEMICOLON */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_SEMICOLON, NULL, NULL},                {LOOKING_FOR_SEMICOLON, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_SEMICOLON, NULL, NULL},                 {LOOKING_FOR_SEMICOLON, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {FINDING_SEMICOLON, NULL, NULL},                     {LOOKING_FOR_SEMICOLON, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL}},

    /* FINDING_SEMICOLON */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_EQUAL, NULL, add_clear_data_type},     {LOOKING_FOR_EQUAL, NULL, add_clear_data_type},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_EQUAL, NULL, add_clear_data_type},      {LOOKING_FOR_EQUAL, NULL, add_clear_data_type},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {LOOKING_FOR_EQUAL, NULL, add_clear_data_type},      {LOOKING_FOR_EQUAL, NULL, add_clear_data_type}},

    /* LOOKING_FOR_EQUAL */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_EQUAL, NULL, add_data_type},           {LOOKING_FOR_EQUAL, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_EQUAL, NULL, NULL},                     {LOOKING_FOR_EQUAL, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {LOOKING_FOR_EQUAL, NULL, NULL},                     {FINDING_EQUAL, NULL, add_data_type},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {LOOKING_FOR_EQUAL, NULL, NULL},                     {LOOKING_FOR_EQUAL, NULL, NULL}},

    /* FINDING_EQUAL */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},     {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},      {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},      {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {ST_END_N, NULL, NULL},                              {ST_END_R, NULL, NULL}},

    /* LOOKING_FOR_BOUNDARY_END */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},     {LOOKING_FOR_BOUNDARY_END, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},      {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {LOOKING_FOR_BOUNDARY_END, NULL, NULL},              {LOOKING_FOR_BOUNDARY_END, copy_to_data, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {ST_END_N, NULL, NULL},                              {ST_END_R, NULL, NULL}},

    /* LOOKING_FOR_ST_END */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_ST_END, copy_to_data, NULL},           {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_ST_END, copy_to_data, NULL},            {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {LOOKING_FOR_ST_END, copy_to_data, NULL},            {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {ST_END_N, NULL, NULL},                              {ST_END_R, NULL, NULL}},

    /* ST_END_N */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_DATA_TYPE, NULL, add_clear_data_type}, {WAITING_FOR_SPACE, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {TITLE_END, NULL, NULL},                             {ST_END, NULL, NULL}},

    /* ST_END_R */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_DATA_TYPE, NULL, add_clear_data_type}, {WAITING_FOR_SPACE, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {ST_END, NULL, NULL},                                {TITLE_END, NULL, NULL}},

    /* ST_END */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_DATA_TYPE, NULL, add_clear_data_type}, {WAITING_FOR_SPACE, copy_to_data, NULL},
    /* COLON */                                          /* SLASH */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {TITLE_END, NULL, NULL},                             {TITLE_END, NULL, NULL}},

    /* WAITING_FOR_SPACE */
    /* CHARACTER */                                      /* SPACE */
    {{LOOKING_FOR_ST_END, copy_to_data, NULL},           {WAITING_FOR_SPACE, NULL, NULL},
    /* COLON */                                          /* SLASH */
    {LOOKING_FOR_ST_END, copy_to_data, NULL},            {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* SEMICOLON */                                      /* EQUAL */
    {LOOKING_FOR_ST_END, copy_to_data, NULL},            {LOOKING_FOR_ST_END, copy_to_data, NULL},
    /* ST_END_CHARACTER_N */                             /* ST_END_CHARACTER_R */
    {STATE_ERROR, NULL, NULL},                           {STATE_ERROR, NULL, NULL}},
};

rule_t get_syntax(state_t state, lexem_t lexem) {
    return syntax[state][lexem];
}
