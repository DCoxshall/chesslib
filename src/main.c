#include <stddef.h>
#include <stdio.h>

#include "Game.h"

int
main()
{
	Game_t game = game_init();
	game.current_position.piece_bitboards[0][5] = (uint64_t)1 << H8;
	game_show(&game);
}