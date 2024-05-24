#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "Position.h"

Game_t*
game_init()
{
	Game_t* new_game = malloc(sizeof(Game_t));
	new_game->current_position = position_init();
	new_game->position_stack = NULL;
	return new_game;
}

/// FEN PARSING FUNCTIONS ///

static int
parse_state_fen(Game_t *game, const char *token)
{
	if (token == NULL)
		return 1;
	Square_t square = A8;
	while (*token != 0) {
		if (strchr("PRNQBKprnbqk", *token)) {
			position_place_piece(game->current_position, square,
			    *token);
			square += 8;
		} else if (strchr("12345678", *token)) {
			square += 8 * (*token - '0');
		} else if (*token == '/') {
			square -= 65;
		} else {
			return 1;
		}
		token++;
	}
	if (square != 64)
		return 1;
	return 0;
}

static int
parse_turn_fen(Game_t *game, const char *token)
{
	if (!strcmp("w", token)) {
		game->current_position->turn = WHITE;
	} else if (!strcmp("b", token)) {
		game->current_position->turn = BLACK;
	} else {
		return 1;
	}
	return 0;
}

static int
parse_castling_fen(Game_t *game, char *token)
{

	char *options[] = { "-", "q", "k", "kq", "Q", "Qq", "Qk", "Qkq", "K",
		"Kq", "Kk", "Kkq", "KQ", "KQq", "KQk", "KQkq" };
	for (int i = 0; i < 16; i++) {
		if (!strcmp(token, options[i])) {
			game->current_position->castling_rights = i;
			return 0;
		}
	}
	return 1;
}

static int
parse_en_passant_fen(Game_t *game, const char *token)
{
	if (!strcmp(token, "-")) {
		game->current_position->en_passant_target = NONE;
		return 0;
	}

	if (strlen(token) != 2)
		return 1;

	if (token[0] < 'a' || token[0] > 'h')
		return 1;

	if (token[1] < '1' || token[1] > '8')
		return 1;

	char *alphabet = "abcdefgh";
	char *numbers = "12345678";
	int file_no = (int)(strchr("abcdefgh", token[0]) - alphabet);
	int rank_no = (int)(strchr("12345678", token[0]) - numbers);

	game->current_position->en_passant_target = file_no * 8 + rank_no;
	return 0;
}

static int
parse_move_fen(int *moves, char *token)
{
	char *c = token;
	while (*c) {
		if (*c < '0' || *c > '9')
			return 1;
		c += 1;
	}
	*moves = atoi(token);
	return 0;
}

int
game_parse_fen(Game_t *game, const char *orig_fen)
{
	// Create a new game to parse into. If the entire FEN is parsed
	// successfully into this game, copy the position into the original
	// game. If not, the original game is left untouched.
	Game_t* new_game = game_init();
	// Create a new FEN string to operate on, since we don't want to change
	// the original FEN.
	char *fen;
	// 6 fields - state, turn, castling, en passant, half/full moves.
	char *fields[6];

	// Duplicate the original FEN string.
	fen = strdup(orig_fen);

    // Split FEN into its 6 fields.
	fields[0] = strtok(fen, " ");
	for (int i = 1; i < 6; i++) {
		fields[i] = strtok(NULL, " ");
		if (fields[i] == NULL) {
			free(fen);
            free(new_game);
			return 7;
		}
	}

	// There's more data than just the 6 fields we want; an invalid FEN.
	if (strtok(NULL, " ") != NULL) {
		free(fen);
        free(new_game);
		return 7;
	}

	// Parse state
	if (parse_state_fen(new_game, fields[0]) == 1) {
		free(fen);
        free(new_game);
		return 1;
	}

	// Parse turn
	if (parse_turn_fen(new_game, fields[1]) == 1) {
		free(fen);
        free(new_game);
		return 2;
	}

	// Parse castling.
	if (parse_castling_fen(new_game, fields[2]) == 1) {
		free(fen);
        free(new_game);
		return 3;
	}

	// Parse en passant square.
	if (parse_en_passant_fen(new_game, fields[3]) == 1) {
		free(fen);
        free(new_game);
		return 4;
	}

	// Parse half and full moves
	if (parse_move_fen(&new_game->current_position->half_moves, fields[4]) ==
	    1) {
		free(fen);
        free(new_game);
		return 5;
	}
	if (parse_move_fen(&new_game->current_position->full_moves, fields[5]) ==
	    1) {
		free(fen);
        free(new_game);
		return 6;
	}

	// If every field has parsed correctly, copy data from temporary game
	// into permanent game and return.
	memcpy(game, new_game, sizeof(Game_t));
	free(fen);
    free(new_game);
	return 0;
}

static void
square_to_string(Square_t square, char string[3])
{
	if (square == -1) {
		string[0] = '-';
		string[1] = 0;
	} else {
		string[0] = "abcdefgh"[square / 8];
		string[1] = "12345678"[square % 8];
		string[2] = 0;
	}
}

void
game_show(Game_t *game)
{
	char *pieces = "PRNBQKprnbqk";
	char grid[64] = { 0 };
	Bitboard_t *bbs = game->current_position->piece_bitboards;

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

	char en_passant_square[3];
	char castling[5] = { '-', 0, 0, 0, 0 };
	char turn;

	square_to_string(game->current_position->en_passant_target,
	    en_passant_square);

	int j = 0;
	uint8_t rights = game->current_position->castling_rights;
	for (int i = 3; i >= 0; i--) {
		if (((rights >> i) & 1) == 1) {
			castling[j] = "qkQK"[i];
			j++;
		}
	}

	if (game->current_position->turn == WHITE) {
		turn = 'w';
	} else {
		turn = 'b';
	}

	printf("%c %s %s %d %d\n", turn, castling, en_passant_square,
	    game->current_position->half_moves,
	    game->current_position->full_moves);
}