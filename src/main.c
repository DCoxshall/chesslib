#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "Position.h"

int
main()
{
	Position_t *pos = position_init();
	int res = position_parse_fen(pos,
	    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQk h8 0 1");
	printf("FEN parse result: %d\n", res);
	position_show(pos);
}