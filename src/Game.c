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

static void
fill_square(Square_t square, char *grid, Bitboard_t bitboards[2][6])
{
	char piece = '.';
	for (int color = 0; color < 2; color++) {
		for (int type = 0; type < 6; type++) {
			if (((bitboards[color][type] >> square) & 1) == 1) {
				switch (type) {
				case 0:
					piece = 'p';
					break;
				case 1:
					piece = 'r';
					break;
				case 2:
					piece = 'n';
					break;
				case 3:
					piece = 'b';
					break;
				case 4:
					piece = 'q';
					break;
				case 5:
					piece = 'k';
					break;
				}
				if (color == 0) {
					piece = toupper(piece);
				}
			}
		}
	}
	if (piece)
		grid[square] = piece;
}

void
game_show(Game_t *game)
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
		}
	}
	char grid[64];
	for (int rank = 7; rank > -1; rank--) {
		for (int file = 0; file < 8; file++) {
			Square_t square = file * 8 + rank;
			fill_square(square, grid,
			    game->current_position.piece_bitboards);
		}
	}

	for (int rank = 7; rank >= 0; rank--) {
		for (int file = 0; file < 8; file++) {
			printf("%c ", grid[file * 8 + rank]);
		}
		printf("\n");
	}
}
