#include <stddef.h>
#include <stdio.h>

#include "Game.h"

int
main()
{
	Game_t game = game_init();
	game.current_position.piece_bitboards[0] = (uint64_t)1 << A8;
	game.current_position.piece_bitboards[1] |= (uint64_t)1 << A1;
	game.current_position.piece_bitboards[2] |= (uint64_t)1 << H1;
	game.current_position.piece_bitboards[3] |= (uint64_t)1 << H8;

	game_show(&game);
}