#ifndef LIST_H
#define LIST_H

struct list_node_s;
typedef struct list_node_s list_node_t;

typedef struct list_node_s {
	list_node_t *prev;
	list_node_t *next;
	int value;
} list_node_t;

typedef struct {
	list_node_t *first;
	list_node_t *last;
} list_t;

list_t *list_create();
void list_destroy(list_t *list);
int list_insert(list_t *list, list_node_t *node, int value);
int list_push_front(list_t *list, int value);
int list_push_back(list_t *list, int value);
int list_remove(list_t *list, list_node_t *node);
int list_pop_front(list_t *list);
int list_pop_back(list_t *list);

#endif
