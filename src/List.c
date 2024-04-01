#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"

List_t *
list_push(List_t *list, Position_t position)
{
	List_t *new_list = malloc(sizeof(List_t));
	new_list->position = position;
	if (list == NULL) {
		new_list->next = NULL;
	} else {
		new_list->next = list;
	}
	return new_list;
}

List_t *
list_pop(List_t *list, Position_t *position)
{
	if (list == NULL) {
		return NULL;
	}
	memcpy(position, &list->position, sizeof(Position_t));
	List_t *new_list = list->next;
	free(list);
	return new_list;
}