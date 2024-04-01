#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "Position.h"

Game_t
game_init()
{
	Game_t new_game;
	new_game.current_position = position_init();
	new_game.position_stack = NULL;
	return new_game;
}

// // TODO
// int
// game_parse_fen(Game_t *game, const char *orig_fen)
// {
// 	// Create a new game to parse into. If the entire FEN is parsed
// 	// successfully into this game, copy the position into the original
// 	// game. If not, the original game is left untouched.
// 	Game_t new_game;
// 	char *token;
// 	char *fen;

// 	fen = strdup(orig_fen);

// 	/* Parse each field of the FEN in order. */
// 	token = strtok(fen, " ");
// 	if (token == NULL) {
// 		free(fen);
// 		free(token);
// 		return 1;
// 	}

// 	return 0;
// }

void
game_show(Game_t *game)
{
	char *pieces = "PRNBQKprnbqk";
	char grid[64] = { 0 };
	Bitboard_t *bbs = game->current_position.piece_bitboards;

	for (int grid_i = 0; grid_i < 64; grid_i++) {
		for (int piece_i = 0; piece_i < 12; piece_i++) {
			if (((bbs[piece_i] >> grid_i) & 1) == 1) {
				grid[grid_i] = pieces[piece_i];
			}
		}
		if (grid[grid_i] == 0) {
			grid[grid_i] = '.';
		}
	}

	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			printf("%c ", grid[file * 8 + rank]);
		}
		printf("\n");
	}
}