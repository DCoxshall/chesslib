#ifndef _LIST_H_
#define _LIST_H_

#include "Position.h"

typedef struct List {
	Position_t position;
	struct List *next;
} List_t;

/* Adds a position to the start of the list. */
List_t *list_push(List_t *list, Position_t position);

/* Copy all data from the last position on the list into `position`, and return
 * the new list with the last position removed. Will return nothing if the list
 * is empty.*/
List_t *list_pop(List_t *list, Position_t *position);

#endif