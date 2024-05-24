#include <stddef.h>
#include <stdio.h>

#include "Game.h"

int
main()
{
	Game_t game = game_init();

	printf("FEN parsing result: %d\n",
	    game_parse_fen(&game,
		"r3kbnr/p4ppp/2n1p3/qN6/P2pP3/5N2/1P3PPP/R1BQ1RK1 w Qq - 0 11"));

	game_show(&game);
}