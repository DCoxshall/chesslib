#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Position.h"

int
main()
{
	Position_t *pos = position_init();
	int res = position_parse_fen(pos, "rnbqkbnr/pppppppp/8/8/8/5BN1/PPPPPPPP/RNBQK2R w KQkq - 0 1");
	printf("FEN parse result: %d\n", res);
	position_show(pos);

	Move_t move = { .destination = G1,
		.start = E1,
		.promotion_piece = { .present = false, .value = 4 } };

	res = position_make_move(&pos, &move);
	printf("move result: %d\n", res);
	position_show(pos);
}