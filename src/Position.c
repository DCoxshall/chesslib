#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Position.h"

/// MISC. BOARD FUNCTIONS ///

char
piece_to_char(const Piece_t piece)
{
	if (piece.team == BLACK)
		return "PRNBQKprnbqk"[piece.type + 6];
	return "PRNBQKprnbqk"[piece.type];
}

static char
piece_at_square(Position_t *position, Square_t square)
{
	// This function assumes that the board is "valid" (i.e. there is only
	// one piece on a given square).
	for (int i = 0; i < 12; i++) {
		if (((position->piece_bitboards[i] >> square) & 1) == 1) {
			return "PRNBQKprnbqk"[i];
		}
	}
	return '.';
}

// Clears the square in every bitboard stored in `position`.
static void
position_clear_square(Position_t *position, Square_t square)
{
	for (int i = 0; i < 12; i++) {
		position->piece_bitboards[i] &= ~((Bitboard_t)1 << square);
	}
}

/// MOVE FUNCTIONS ///

static void
position_place_piece(Position_t *position, Square_t square, Piece_t piece)
{
	// Ensure that no other piece is also on that square.
	position_clear_square(position, square);
	int bitboard_index = (piece.team * 6) + piece.type;
	position->piece_bitboards[bitboard_index] |= ((Bitboard_t)1 << square);
}

void
position_flip_turn(Position_t *position)
{
	position->turn = (position->turn == WHITE) ? BLACK : WHITE;
}

/// DISPLAY FUNCTIONS ///

static void
castling_to_string(CastlingRights_t rights, char string[5])
{
	char *castling_strings[] = { "-", "q", "k", "kq", "Q", "Qq", "Qk",
		"Qkq", "K", "Kq", "Kk", "Kkq", "KQ", "KQq", "KQk", "KQkq" };
	memset(string, 0, 5);
	strcpy(string, castling_strings[rights]);
}

char *
square_to_string(Square_t square)
{
	char *square_str = malloc(3);
	char *alphabet = "abcdefgh";
	char *numbers = "12345678";
	square_str[0] = alphabet[square % 8];
	square_str[1] = numbers[square / 8];
    square_str[2] = 0;
	return square_str;
}

char *
move_to_string(const Move_t move)
{
	size_t str_len = (move.promotion_piece.present) ? 6 : 5;
	char *move_str = malloc(str_len);
	memset(move_str, 0, str_len);
	char *start_square_string = square_to_string(move.start);
	char *destination_square_string = square_to_string(move.destination);
	strcat(move_str, start_square_string);
	strcat(move_str, destination_square_string);
	if (move.promotion_piece.present) {
		move_str[4] = "prnbqk"[move.promotion_piece.value];
	}
	free(start_square_string);
	free(destination_square_string);
	return move_str;
}

void
position_show(Position_t *position)
{
	char turn;
	char castling[5] = { 0 };
	// char en_passant[3] = { 0 };
	char *en_passant;

	// TODO change loop to remove these variables.
	Square_t square = A8;
	int ctr = 0;

	turn = (position->turn == WHITE) ? 'w' : 'b';
	castling_to_string(position->castling_rights, castling);
	if (position->en_passant_target.present) {
		en_passant = square_to_string(
		    position->en_passant_target.value);
	} else {
		en_passant = "-";
	}

	while (ctr < 64) {
		printf("%c ", piece_at_square(position, square));
		if (((square) + 1) % 8 == 0) {
			square -= 16;
			printf("\n");
		}
		square++;
		ctr++;
	}

	printf("%c %s %s %d %d\n", turn, castling, en_passant,
	    position->half_moves, position->full_moves);
}

/// FEN FUNCTIONS ///

static int
parse_state_fen(Position_t *position, const char *token)
{
	if (token == NULL)
		return 1;
	Square_t square = A8;
	Piece_t piece;
	while (*token != 0) {
		if (piece_init(&piece, *token) == 0) {
			position_place_piece(position, square, piece);
			square += 1;
		} else if (strchr("12345678", *token)) {
			square += (*token - '0');
		} else if (*token == '/') {
			square -= 16;
		} else {
			return 1;
		}
		token++;
	}
	if (square != 8)
		return 1;
	return 0;
}

static int
parse_turn_fen(Position_t *position, const char *token)
{
	if (!strcmp("w", token)) {
		position->turn = WHITE;
	} else if (!strcmp("b", token)) {
		position->turn = BLACK;
	} else {
		return 1;
	}
	return 0;
}

static int
parse_castling_fen(Position_t *position, char *token)
{
	char *options[] = { "-", "q", "k", "kq", "Q", "Qq", "Qk", "Qkq", "K",
		"Kq", "Kk", "Kkq", "KQ", "KQq", "KQk", "KQkq" };
	for (int i = 0; i < 16; i++) {
		if (!strcmp(token, options[i])) {
			position->castling_rights = i;
			return 0;
		}
	}
	return 1;
}

static int
parse_en_passant_fen(Position_t *position, const char *token)
{
	if (!strcmp(token, "-")) {
		position->en_passant_target.present = false;
		return 0;
	} else {
		position->en_passant_target.present = true;
	}

	if (strlen(token) != 2)
		return 1;

	if (token[0] < 'a' || token[0] > 'h' || token[1] < '1' ||
	    token[1] > '8')
		return 1;

	char *alphabet = "abcdefgh";
	char *numbers = "12345678";
	int file_no = (int)(strchr("abcdefgh", token[0]) - alphabet);
	int rank_no = (int)(strchr("12345678", token[1]) - numbers);

	position->en_passant_target.value = file_no * 8 + rank_no;
	return 0;
}

static int
parse_move_fen(int *moves, char *token)
{
	char *c = token;
	while (*c) {
		if (*c < '0' || *c > '9')
			return 1;
		c++;
	}
	*moves = atoi(token);
	return 0;
}

int
position_parse_fen(Position_t *position, const char *orig_fen)
{
	// Create a new game to parse into. If the entire FEN is parsed
	// successfully into this game, copy the position into the original
	// game. If not, the original game is left untouched.
	Position_t *new_position = position_init();
	// Create a new FEN string to operate on, since we don't want to change
	// the original FEN.
	char *fen;
	// 6 fields - state, turn, castling, en passant, half/full moves.
	char *fields[6];

	// Duplicate the original FEN string.
	fen = malloc(strlen(orig_fen) + 1);
	strcpy(fen, orig_fen);

	// Split FEN into its 6 fields.
	fields[0] = strtok(fen, " ");
	for (int i = 1; i < 6; i++) {
		fields[i] = strtok(NULL, " ");
		if (fields[i] == NULL) {
			free(fen);
			free(new_position);
			return 7;
		}
	}

	// There's more data than just the 6 fields we want; an invalid FEN.
	if (strtok(NULL, " ") != NULL) {
		free(fen);
		free(new_position);
		return 7;
	}

	// Parse state
	if (parse_state_fen(new_position, fields[0]) == 1) {
		free(fen);
		free(new_position);
		return 1;
	}

	// Parse turn
	if (parse_turn_fen(new_position, fields[1]) == 1) {
		free(fen);
		free(position);
		return 2;
	}

	// Parse castling.
	if (parse_castling_fen(new_position, fields[2]) == 1) {
		free(fen);
		free(new_position);
		return 3;
	}

	// Parse en passant square.
	if (parse_en_passant_fen(new_position, fields[3]) == 1) {
		free(fen);
		free(new_position);
		return 4;
	}

	// Parse half and full moves
	if (parse_move_fen(&new_position->half_moves, fields[4]) == 1) {
		free(fen);
		free(new_position);
		return 5;
	}

	if (parse_move_fen(&new_position->full_moves, fields[5]) == 1) {
		free(fen);
		free(new_position);
		return 6;
	}

	// If every field has parsed correctly, copy data from temporary game
	// into permanent game and return.
	memcpy(position, new_position, sizeof(Position_t));
	free(fen);
	free(new_position);
	return 0;
}

int
piece_init(Piece_t *piece, const char token)
{
	int piece_index;
	char *alphabet = "PRNBQKprnbqk";
	char *alphabet_index = strchr(alphabet, token);
	if (alphabet_index == NULL)
		return 1;

	piece_index = (int)(alphabet_index - alphabet);
	piece->type = piece_index % 6;
	piece->team = piece_index / 6;
	return 0;
}

Position_t *
position_init()
{
	Position_t *new_pos = malloc(sizeof(Position_t));
	for (int i = 0; i < 12; i++) {
		new_pos->piece_bitboards[i] = 0;
	}
	new_pos->turn = WHITE;
	new_pos->castling_rights = KQkq;
	new_pos->en_passant_target.present = false;
	new_pos->half_moves = 0;
	new_pos->full_moves = 0;
	new_pos->prev_position = NULL;
	return new_pos;
}
