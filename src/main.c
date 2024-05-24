#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Game.h"
#include "List.h"

int
main()
{
    List_t* list = list_init(sizeof(int)); 
    int* elems[100];
    for (int i = 0; i < 100; i++) {
        elems[i] = malloc(sizeof(int));
        *elems[i] = i + 1;
        list_push(list, elems[i]);
    }
    for (int i = 0; i < 100; i++) {
        int item = 0;
        list_pop(list, &item);
        printf("%d\n", item);
    }
    free(list);
}