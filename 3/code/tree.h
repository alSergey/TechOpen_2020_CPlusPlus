#ifndef TREE_H
#define TREE_H

struct tree_node_s;
typedef struct tree_node_s tree_node_t;

typedef struct tree_node_s {
	tree_node_t *parent;
	tree_node_t *left;
	tree_node_t *right;
	int value;
} tree_node_t;

typedef struct {
	tree_node_t *root;
} tree_t;

tree_t *tree_create();
void tree_destroy(tree_t *tree);
int tree_insert(tree_t *tree, int value);
int tree_remove(tree_t *tree, int value);
int tree_find(tree_t *tree, int value);
typedef void (*tree_traverse_cb)(int value, void *data);
void tree_traverse(tree_t *tree, tree_traverse_cb cb, void *data);

#endif
