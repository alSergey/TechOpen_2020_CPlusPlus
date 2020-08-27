#include <stdlib.h>

#include "tree.h"

tree_t *tree_create() {
	tree_t *tree = calloc(1, sizeof(tree_t));
	return tree;
}

static void tree_destroy_node(tree_node_t *node) {
	if (!node)
		return;
	tree_destroy_node(node->left);
	tree_destroy_node(node->right);
	free(node);
}

void tree_destroy(tree_t *tree) {
	tree_destroy_node(tree->root);
	free(tree);
}

static tree_node_t *tree_find_helper(tree_t *tree, int value, int mode_insert) {

	tree_node_t *node = tree->root;
	while (node) {
		if (value == node->value && !mode_insert)
			break;
		else if (value <= node->value) {
			if (node->left)
				node = node->left;
			else
				break;
		}
		else {
			if (node->right)
				node = node->right;
			else
				break;
		}
	}

	return node;
}

int tree_insert(tree_t *tree, int value) {
	tree_node_t *new_node = calloc(1, sizeof(tree_node_t));
	if (!new_node)
		return -1;
	new_node->value = value;

	tree_node_t *parent = tree_find_helper(tree, value, 1);
	if (!parent)
		tree->root = new_node;
	else {
		if (value <= parent->value)
			parent->left = new_node;
		else
			parent->right = new_node;
		new_node->parent = parent;
	}
	return 0;
}

int tree_remove(tree_t *tree, int value) {
	tree_node_t *node = tree_find_helper(tree, value, 0);;

	if (!node)
		return -1;

	if (!node->left && !node->right) {
		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left == NULL;
			else
				node->parent->right == NULL;
		}
		else
			tree->root = NULL;
	}
	else if ((!node->left && node->right) || (node->left && !node->right)) {
		tree_node_t *child = (node->left) ? node->left : node->right;
		if (node->parent) {
			if (node->parent->left == node)
				node->parent->left = child; 
			else
				node->parent->right = child; 
		}
		else
			tree->root = child;
		child->parent = node->parent;
	}
	else {
		tree_node_t *swap = node->left;
		while (swap->right)
			swap = swap->right;
		node->value = swap->value;
		if (swap->parent->left == swap)
			swap->parent->left = swap->left;
		else
			swap->parent->right = swap->left;
		node = swap;
	}
	free(node);
	return 0;
}

int tree_find(tree_t *tree, int value) {
	return (tree_find_helper(tree, value, 0) != NULL);
}

static void tree_traverse_node(tree_node_t *node, tree_traverse_cb cb, void *data) {
	if (!node)
		return;
	tree_traverse_node(node->left, cb, data);
	cb(node->value, data);
	tree_traverse_node(node->right, cb, data);
}

void tree_traverse(tree_t *tree, tree_traverse_cb cb, void *data) {
	tree_traverse_node(tree->root, cb, data);
}
