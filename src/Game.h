#ifndef _GAME_H_
#define _GAME_H_

#include "List.h"
#include "Position.h"

typedef struct Game {
	Position_t current_position;
	List_t *position_stack;
} Game_t;

Game_t game_init();

/* Pretty print the game to output. */
void game_show(Game_t *game);

/* Parses a FEN string into a game. This function does not check for board
 * validity - it will happily parse a FEN representing an illegal position. If
 * the FEN string is rejected for any reason, this function will return 1, and
 * the original game struct will not have been edited in any way. */
int game_parse_fen(Game_t *game, const char *fen);

#endif