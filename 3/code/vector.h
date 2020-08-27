#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct {
	int *data;
	size_t length;
	size_t capacity;
} vector_t;

vector_t *vector_create();
void vector_destroy(vector_t *vector);
int vector_insert(vector_t *vector, int index, int value);
int vector_push_back(vector_t *vector, int value);
int vector_pop_back(vector_t *vector, int value);
int vector_remove(vector_t *vector, int index);
 
#endif
