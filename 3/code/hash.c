#include "hash.h"

hash_t *hash_create(size_t index_size) {
	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;
	hash->index = calloc(index_size, sizeof(hash_node_t*));
	if (!hash->index) {
		free(hash);
		return NULL;
	}
	hash->index_size = index_size;
	return hash;
}

void hash_destroy(hash_t *hash) {
	size_t i;
	for (i = 0; i < hash->index_size; i++) {
		hash_node_t *node = hash->index[i];
		while (node) {
			hash_node_t *next = node->next;
			free(node);
			node = next;
		}
	}
	free(hash->index);
	free(hash);
}

int hash_insert(hash_t *hash, int key, int value) {
	int hkey = key % hash->index_size;
	hash_node_t *node = hash->index[hkey];
	while (node && node->key != key)
		node = node->next;

	if (!node) {
		hash_node_t *new_node = malloc(sizeof(hash_node_t));
		if (!new_node)
			return -1;
		new_node->next = hash->index[hkey];
		new_node->key = key;
		new_node->value = value;
		hash->index[hkey] = new_node;
	}
	else
		node->value = value;

	return 0;
}

int hash_remove(hash_t *hash, int key) {
	int hkey = key % hash->index_size;
	hash_node_t *prev_node = NULL;
	hash_node_t *node = hash->index[hkey];

	while (node && node->key != key) {
		prev_node = node;
		node = node->next;
	}

	if (!node)
		return -1;

	if (!prev_node)
		hash->index[hkey] = node->next;
	else
		prev_node->next = node->next;

	free(node);
	return 0;
}

int hash_get(hash_t *hash, int key) {

	int hkey = key % hash->index_size;
	hash_node_t *node = hash->index[hkey];

	while (node && node->key != key)
		node = node->next;

	if (!node)
		return -1;

	return node->value;
}
