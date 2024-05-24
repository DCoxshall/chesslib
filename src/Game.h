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
 * the FEN string is rejected for any reason, this function will return a number
 * between 1 and 7 inclusive, representing the field of the FEN that wouldn't
 * parse, with 7 representing a length/form problem. The original game struct
 * will not have been edited in any way unless every field parses correctly. On
 * success, it will return 0; */
int game_parse_fen(Game_t *game, const char *fen);

#endif