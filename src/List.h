#ifndef _LIST_H_
#define _LIST_H_

// Homogeneous list data structure.

typedef struct Node {
	void *value;
	struct Node *next;
	struct Node *prev;
} Node_t;

typedef struct List {
	Node_t *head;
	Node_t *tail;
	size_t length;
    size_t elem_size; // Size in bytes of each element.
} List_t;

// Creates a new, empty list.
List_t *list_init(size_t elem_size);

// Adds a new value to the end of the list. `new_value` must be allocated on the
// heap. This function doesn't make a copy of the value - it just stores a pointer to it in memory.
int list_push(List_t *list, void *new_value);

// Copy all data from the last element on the list into `location`, and return
// the new list with the last position removed. Will return the list unedited if
// the list is empty.
int list_pop(List_t *list, void *location);

#endif