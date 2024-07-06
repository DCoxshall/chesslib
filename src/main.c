#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Position.h"

int
main()
{
    char* res = malloc(100);
    free(res);
	Move_t move = { .destination = E8,
		.start = E7,
		.promotion_piece.present = true,
		.promotion_piece.value = QUEEN };
    res = move_to_string(move);
    printf("%s\n", res);
}