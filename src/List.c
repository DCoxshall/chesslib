#include <stdlib.h>

#include "List.h"
#include <string.h>

List_t *
list_init(size_t elem_size)
{
	List_t *new_list = malloc(sizeof(List_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->length = 0;
    new_list->elem_size = elem_size;
    return new_list;
}

int
list_push(List_t *list, void *new_value)
{
    Node_t* new_node = malloc(sizeof(Node_t));
    new_node->value = new_value;
    
    if (list->length == 0) {
        new_node->next = NULL;
        new_node->prev = NULL;
        list->head = new_node;
        list->tail = new_node;       
    } else {
        new_node->prev = list->tail;
        new_node->next = NULL;
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->length++;
    return 0;
}

int list_pop(List_t* list, void* location) {
    if (list->length == 0){
        return 1;
    }
    memcpy(location, list->tail->value, list->elem_size);
    if (list->length == 1) {
        free(list->tail->value);
        free(list->tail);
        list->tail = NULL;
        list->head = NULL;
    } else {
        void* tmp = list->tail->prev;
        free(list->tail->value);
        free(list->tail);
        list->tail = tmp;
    }
    list->length--;
    return 0;
}