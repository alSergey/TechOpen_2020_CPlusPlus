#include <stdlib.h>
#include <string.h>

#include "vector.h"

vector_t *vector_create() {
	vector_t *vector = calloc(1, sizeof(vector_t));
	return vector;
}

void vector_destroy(vector_t *vector) {
	free(vector->data);
	free(vector);
}

int vector_insert(vector_t *vector, int index, int value) {
	if (index < 0 || index > vector->length)
		return -1;
	if (vector->length == vector->capacity) {
		size_t new_capacity = (vector->capacity ? vector->capacity : 1) * 2;
		int *new_data = realloc(vector->data, new_capacity * sizeof(int));
		if (!new_data) return -1;
		vector->data = new_data;
		vector->capacity = new_capacity;
	}
	if (index < vector->length)
		memmove(&vector->data[index], &vector->data[index + 1], sizeof(int) * (vector->length - index));
	vector->data[index] = value;
	vector->length++;
	return 0;
}

int vector_push_back(vector_t *vector, int value) {
	return vector_insert(vector, vector->length, value);
}

int vector_pop_back(vector_t *vector, int value) {
	if (vector->length == 0)
		return -1;
	int last = vector->data[vector->length - 1];
	vector->length--;
	return last;
}

int vector_remove(vector_t *vector, int index) {
	if (index < 0 || index >= vector->length)
		return -1;
	if (index < vector->length - 1)
		memmove(&vector->data[index], &vector->data[index + 1], sizeof(int) * (vector->length - 1 - index));
	vector->length--;
	return 0;
}
