#ifndef HASH_H
#define HASH_H

#include <stdlib.h>

struct hash_node_s;
typedef struct hash_node_s hash_node_t;

typedef struct hash_node_s {
       hash_node_t *next;
       int key;
       int value;
} hash_node_t;

typedef struct {
       hash_node_t **index;
       size_t index_size;
} hash_t;

hash_t *hash_create(size_t index_size);
void hash_destroy(hash_t *hash);
int hash_insert(hash_t *hash, int key, int value);
int hash_remove(hash_t *hash, int key);
int hash_get(hash_t *hash, int key);

#endif
