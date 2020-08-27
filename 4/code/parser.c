#include <stdio.h>
#include <string.h>

// Состояния в которых может быть парсер
typedef enum {
	STATE_BEGIN = 0,
	STATE_INT,
	STATE_INT_DIGIT,
	STATE_DOT,
	STATE_FRACT_BEGIN,
	STATE_FRACT,
	STATE_EXP_BEGIN,
	STATE_EXP,
	STATE_EXP_DIGIT,
	STATE_COUNT, // элементы в enum нумеруются по порядку, STATE_COUNT содержит количество состояний, для которых есть переходы в другие состояния
	STATE_END,
	STATE_ERROR
} state_t;

// Входные лексемы (группы из одного или нескольких символов)
typedef enum {
	LEXEM_NUL = 0,
	LEXEM_DIGIT, // [1-9]
	LEXEM_SIGN, // +-
	LEXEM_DOT, // .
	LEXEM_EXP, // eE
	LEXEM_END, // \0
	LEXEM_COUNT // элементы в enum нумеруются по порядку, LEXEM_COUNT содержит количество лексем
} lexem_t;

// Структура для хранения результата
typedef struct {
	char int_sign; // знак целой части
	int int_part; // целая часть
	int fract_width; // количество цифр дробной части 
	int fract_part; // дробная часть
	char exp_sign; // знак экспоненты
	int exp_part; // экспонента
} data_t;

// Указатель на функцию действия, которая вызывается при некоторых переходах
typedef void (*action_t)(char c, data_t *data);

// Структура правила в таблице переходов
typedef struct {
	state_t state; // Состояние в которое переходит парсер
	action_t action; // Действие которое надо совершить при данном переходе
} rule_t;

// Действие для сохранения знака целой части
void store_int_sign(char c, data_t *data) {
	data->int_sign = c;
}

// Действие для сохранения цифры целой части
void store_int(char c, data_t *data) {
	data->int_part *= 10;
	data->int_part += c - '0';
}

// Действие для сохранения цифры дробной части
void store_fract(char c, data_t *data) {
	data->fract_width++;
	data->fract_part *= 10;
	data->fract_part += c - '0';
}

// Действие для сохранения знака экспоненты
void store_exp_sign(char c, data_t *data) {
	data->exp_sign = c;
}

// Действие для сохранения цифры экспоненты
void store_exp(char c, data_t *data) {
	data->exp_part *= 10;
	data->exp_part += c - '0';
}

// Таблица переходов
// Каждая строка соответствует состоянию в котором может находиться парсер
// Каждый столбец соответствует входной лексеме (текущему символу разбираемой строки)
// Зная текущее состояние и пришедшею лексему по таблице переходов мы определяем новое состояние и необходимое действие
// Эта таблица описывает граф переходов
rule_t syntax[STATE_COUNT][LEXEM_COUNT] = {
		/*NUL*/				/*DIGIT*/			/*SIGN*/			/*DOT*/				/*EXP*/			/*END*/
/*BEGIN*/	{{STATE_DOT, store_int},	{STATE_INT_DIGIT, store_int},	{STATE_INT, store_int_sign},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_ERROR, NULL}},
/*INT*/		{{STATE_DOT, store_int},	{STATE_INT_DIGIT, store_int},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_ERROR, NULL}},
/*INT_DIGIT*/	{{STATE_INT_DIGIT, store_int},	{STATE_INT_DIGIT, store_int},	{STATE_ERROR, NULL},		{STATE_FRACT_BEGIN, NULL},	{STATE_EXP, NULL},	{STATE_END, NULL}},
/*DOT*/		{{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_FRACT_BEGIN, NULL},	{STATE_ERROR, NULL},	{STATE_END, NULL}},
/*FRACT_BEGIN*/	{{STATE_FRACT, store_fract},	{STATE_FRACT, store_fract},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_ERROR, NULL}},
/*FRACT*/	{{STATE_FRACT, store_fract},	{STATE_FRACT, store_fract},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_EXP_BEGIN, NULL}, {STATE_END, NULL}},
/*EXP_BEGIN*/	{{STATE_EXP_DIGIT, NULL},	{STATE_EXP_DIGIT, store_exp},	{STATE_EXP, store_exp_sign},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_ERROR, NULL}},
/*EXP*/		{{STATE_EXP_DIGIT, NULL},	{STATE_EXP_DIGIT, store_exp},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_END, NULL}},
/*EXP_DIGIT*/	{{STATE_EXP_DIGIT, store_exp},	{STATE_EXP_DIGIT, store_exp},	{STATE_ERROR, NULL},		{STATE_ERROR, NULL},		{STATE_ERROR, NULL},	{STATE_END, NULL}},
};

// Возвращает лексему по символу. Одна лексема может обозначать целую группу символов.
// В общем случа лексема может состоять из нескольких символов, например, строка в кавычках.
lexem_t get_lexem(char c) {
	switch (c) {
		case '0':
			return LEXEM_NUL;
		case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
			return LEXEM_DIGIT;
		case '-': case '+':
			return LEXEM_SIGN;
		case '.':
			return LEXEM_DOT;
		case 'e': case 'E':
			return LEXEM_EXP;
		case '\0':
			return LEXEM_END;
	}
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
		fprintf(stderr, "Usage: %s number\n", argv[0]);
		return -1;
	}

	char *s = argv[1];
	data_t data;
	memset(&data, 0, sizeof(data));

	// Текущий обрабатываемый символ входной строки
	size_t i = 0;

	// Начальное состояние парсера
	state_t state = STATE_BEGIN;

	// Выполняем парсинг пока парсер не пришел в конечное состояние или в состояние ошибки
	while (state != STATE_END && state != STATE_ERROR) {
		char c = s[i];
		// Получаем лексему по символу
		lexem_t lexem = get_lexem(c);

		// Ищем правило перехода в таблице переходов по текущему состоянию и пришедшей лексеме
		rule_t rule = syntax[state][lexem];
		// Если правило содержит действие, то выполняем его, чтобы парсер мог сохранить результат разбора
		if (rule.action)
			rule.action(c, &data);

		// Переводим парсер в новое состояние
		state = rule.state;

		// Переходим к следующему символу
		i++;
	}

	// Если парсинг закончился ошибкой
	if (state == STATE_ERROR) {
		printf("parse error on position %zu\n", i);
		return -1;
	}

	// Выводим результат
	printf("int_sign %c int %d fract %0*d exp sign %c exp %d\n", data.int_sign, data.int_part, data.fract_width, data.fract_part, data.exp_sign, data.exp_part);

	return 0;
}
