#ifndef PROJECT_INCLUDE_PARSER_H_
#define PROJECT_INCLUDE_PARSER_H_

#include "data.h"

// state_t
typedef enum {
    LOOKING_FOR_DATA_TYPE = 0,
    FINDING_COLON,
    LOOKING_FOR_MULTIPART,
    FINDING_SLASH,
    LOOKING_FOR_SEMICOLON,
    FINDING_SEMICOLON,
    LOOKING_FOR_EQUAL,
    FINDING_EQUAL,
    LOOKING_FOR_BOUNDARY_END,
    LOOKING_FOR_ST_END,
    ST_END_N,
    ST_END_R,
    ST_END,
    WAITING_FOR_SPACE,
    STATE_COUNT,
    STATE_ERROR,
    TITLE_END
} state_t;

// data_type_t
typedef enum {
    FROM = 0,
    TO,
    DATE,
    BOUNDARY,
    CONTENT_TYPE,
    MULTIPART,
    ANOTHER_TYPE
} data_type_t;
data_type_t get_data_type(char* st);

// lexem_t
typedef enum {
    CHARACTER,
    SPACE,
    COLON,
    SLASH,
    SEMICOLON,
    EQUAL,
    ST_END_CHARACTER_N,
    ST_END_CHARACTER_R,
    LEXEM_COUNT
} lexem_t;
lexem_t get_lexem(char c);

// action_t
typedef int (*action_t)(char* st, data_t* data, data_type_t data_type);
int copy_to_data(char* st, data_t* data, data_type_t data_type);

// data_type_action_t
typedef int (*data_type_action_t)(char c, char* data_type_array);
int add_data_type(char c, char* data_type_array);
int add_clear_data_type(char c, char* data_type_array);

// rule_t
typedef struct {
    state_t state;
    action_t action;
    data_type_action_t data_type_action;
} rule_t;
rule_t get_syntax(state_t state, lexem_t lexem);

#endif  // PROJECT_INCLUDE_PARSER_H_
