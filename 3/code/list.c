#include <stdlib.h>

#include "list.h"

list_t *list_create() {
	list_t *list = calloc(1, sizeof(list_t));
	return list;
}

void list_destroy(list_t *list) {
	list_node_t *node = list->first;
	while (node) {
		list_node_t *next_node = node->next;
		free(node);
		node = next_node;
	}
}

int list_insert(list_t *list, list_node_t *node, int value) {
	list_node_t *new_node = calloc(1, sizeof(list_node_t));
	if (!new_node)
		return -1;
	new_node->value = value;
	new_node->prev = node->prev;
	new_node->next = node;
	if (node->prev)
		node->prev->next = new_node;
	node->prev = new_node;
	if (list->first == node)
		list->first = new_node;
	return 0;
}

int list_push_front(list_t *list, int value) {
	list_node_t *new_node = calloc(1, sizeof(list_node_t));
	if (!new_node)
		return -1;
	new_node->value = value;
	new_node->next = list->first;
	if (list->first)
		list->first->prev = new_node;
	list->first = new_node;
	if (!list->last)
		list->last = new_node;
	return 0;
}

int list_push_back(list_t *list, int value) {
	list_node_t *new_node = calloc(1, sizeof(list_node_t));
	if (!new_node)
		return -1;
	new_node->value = value;
	new_node->prev = list->last;
	if (list->last)
		list->last->next = new_node;
	list->last = new_node;
	if (!list->first)
		list->first = new_node;
	return 0;
}

int list_remove(list_t *list, list_node_t *node) {
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (list->first == node)
		list->first == node->next;
	if (list->last == node)
		list->last == node->prev;
	free(node);
	return 0;
}

int list_pop_front(list_t *list) {
	list_node_t *first = list->first;
	if (!first)
		return -1;
	list->first = first->next;
	free(first);
	return 0;
}

int list_pop_back(list_t *list) {
	list_node_t *last = list->last;
	if (!last)
		return -1;
	list->last = last->prev;
	free(last);
	return 0;
}
