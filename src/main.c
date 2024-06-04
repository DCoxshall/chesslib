#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Position.h"

int
main()
{
	Position_t *pos = position_init();
	int res = position_parse_fen(pos,
	    "rnbqkbnr/pppppppp/8/8/8/5BN1/PPPPPPPP/RNBQK2R w KQkq - 0 1");
	printf("FEN parse result: %d\n", res);
	position_show(pos);

	Move_t move = {
		.destination = E4,
		.start = E2,
		.promotion_piece = { .present = true, .value = KING }
	};

    char* repr = move_to_string(move);
    printf("%s\n", repr);
    free(repr);
    free(pos);
}