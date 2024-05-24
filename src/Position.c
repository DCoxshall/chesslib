#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "Position.h"

Position_t
position_init()
{
	Position_t new_pos;
	for (int i = 0; i < 12; i++) {
		new_pos.piece_bitboards[i] = 0;
	}
	new_pos.turn = WHITE;
	new_pos.castling_rights = KQkq;
	new_pos.en_passant_target = NONE;
	new_pos.half_moves = 0;
	new_pos.full_moves = 0;
	return new_pos;
}

int
position_place_piece(Position_t *position, Square_t square, char piece)
{
	char *piece_ptr;
	char *pieces = "PRNBQKprnbqk";
	if ((piece_ptr = strchr(pieces, piece)) == NULL)
		return 1;

	int piece_index = (int)(piece_ptr - pieces);
	position->piece_bitboards[piece_index] |= ((uint64_t)1) << square;
	return 0;
}

