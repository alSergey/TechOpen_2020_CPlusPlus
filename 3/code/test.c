#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "vector.h"
#include "list.h"
#include "tree.h"
#include "hash.h"

#define BUFFER_SIZE 65536

void test_vector() {
	vector_t *vector = vector_create();
	assert(vector != NULL);
	assert(vector_push_back(vector, 1) == 0);
	assert(vector_push_back(vector, 2) == 0);
	assert(vector_push_back(vector, 3) == 0);
	assert(vector_remove(vector, 1) == 0);
	assert(vector_remove(vector, 2) == -1);
	assert(vector_push_back(vector, 4) == 0);
	char buffer[BUFFER_SIZE];
	int offset = 0;
	size_t i;
	for (i = 0; i < vector->length; i++)
		offset += sprintf(buffer + offset, (i == 0) ? "%d" : " %d", vector->data[i]);
	assert(strcmp(buffer, "1 3 4") == 0);
	vector_destroy(vector);
}

void test_list() {
	list_t *list = list_create();
	assert(list != NULL);
	assert(list_push_back(list, 1) == 0);
	assert(list_push_back(list, 2) == 0);
	assert(list_push_front(list, 3) == 0);
	assert(list_insert(list, list->first->next, 4) == 0);
	assert(list_remove(list, list->last->prev) == 0);

	char buffer[BUFFER_SIZE];
	size_t offset;
	list_node_t *node;
       
	offset = 0;
	node = list->first;
	while (node) {
		offset += sprintf(buffer + offset, (offset == 0) ? "%d" : " %d", node->value);
		node = node->next;
	}
	assert(strcmp(buffer, "3 4 2") == 0);

	offset = 0;
	node = list->last;
	while (node) {
		offset += sprintf(buffer + offset, (offset == 0) ? "%d" : " %d", node->value);
		node = node->prev;
	}
	assert(strcmp(buffer, "2 4 3") == 0);

	list_destroy(list);
}

void print_tree_helper(tree_node_t *node, size_t index, char *buffer) {
	if (!node)
		return;
	buffer[index] = '0' + node->value;
	print_tree_helper(node->left, index * 2 + 1, buffer);
	print_tree_helper(node->right, index * 2 + 2, buffer);
}

void print_tree(tree_t *tree, char *buffer, size_t buffer_size) {
	memset(buffer, ' ', buffer_size);
	print_tree_helper(tree->root, 0, buffer);
	ssize_t i;
	for (i = buffer_size - 1; i >= 0; i--) {
		if (buffer[i] == ' ')
			buffer[i] = '\0';
		else
			break;
	}
}

void test_tree_helper(const char *insert_values, int remove_value, const char *expected) {

	tree_t *tree = tree_create();
	assert(tree != NULL);
	size_t i;
	for (i = 0; i < strlen(insert_values); i++)
		assert(tree_insert(tree, insert_values[i] - '0') == 0);
	assert(tree_remove(tree, remove_value) == 0);

	char buffer[BUFFER_SIZE];
	print_tree(tree, buffer, sizeof(buffer));
	assert(strcmp(buffer, expected) == 0);

	tree_destroy(tree);
}

void test_tree() {
	test_tree_helper("6", 6, "");
	test_tree_helper("63", 6, "3");
	test_tree_helper("637", 6, "3 7");
	test_tree_helper("6374", 6, "437");
	test_tree_helper("6372", 6, "327");
	test_tree_helper("6372", 3, "627");
	test_tree_helper("63724", 3, "627 4");
	test_tree_helper("6354", 6, "3 5  4");
	test_tree_helper("63754", 6, "537 4");
}

void test_hash() {
	hash_t *hash = hash_create(64);
	assert(hash != NULL);

	assert(hash_insert(hash, 2, 5) == 0);
	assert(hash_get(hash, 2) == 5);
	assert(hash_get(hash, 3) == -1);

	assert(hash_insert(hash, 2, 6) == 0);
	assert(hash_get(hash, 2) == 6);

	assert(hash_insert(hash, 66, 7) == 0);
	assert(hash_insert(hash, 130, 8) == 0);
	assert(hash_get(hash, 66) == 7);

	assert(hash_remove(hash, 2) == 0);
	assert(hash_get(hash, 66) == 7);

	assert(hash_remove(hash, 130) == 0);
	assert(hash_get(hash, 66) == 7);

	hash_destroy(hash);
}

int main(int argc, char *argv[]) {

	test_vector();
	test_list();
	test_tree();
	test_hash();
	return 0;
}
