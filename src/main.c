#include <stddef.h>
#include <stdio.h>

#include "Game.h"

int
main()
{
	Game_t game = game_init();

	position_place_piece(&game.current_position, A8, 'P');
	position_place_piece(&game.current_position, A1, 'R');
	position_place_piece(&game.current_position, H1, 'N');
	position_place_piece(&game.current_position, H8, 'B');

	game_show(&game);
}